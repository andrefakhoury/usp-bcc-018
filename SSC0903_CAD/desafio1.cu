/**
------------------------------------------------------
--- SSC0903 - Computação de Alto Desempenho (2020) ---
------------------------------------------------------

Atividade 07-4: Atividades em matrizes com CUDA

Desenvolvida por:
- Grupo 1
-- André Luís Mendes Fakhoury
-- Debora Buzon da Silva
-- Gustavo Vinicius Vieira Silva Soares
-- Thiago Preischadt Pinheiro
*/

#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

// numero de threads por bloco
#define BLOCK_SIZE 1024

// encontra o valor minimo e insere em v_min
__global__ void min_kernel(int *v, int N, int *v_min) {
    __shared__ int local_min;
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (threadIdx.x == 0) {
        local_min = v[i];
    }
    __syncthreads();
    if (i < N) {
        atomicMin(&local_min, v[i]);
    }
    __syncthreads();
    if (threadIdx.x == 0) {
        atomicMin(v_min, local_min);
    }
}

// encontra o valor maximo e insere em v_max
__global__ void max_kernel(int *v, int n, int *v_max) {
    __shared__ int local_max;
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (threadIdx.x == 0) {
        local_max = v[i];
    }
    __syncthreads();
    if (i < n) {
        atomicMax(&local_max, v[i]);
    }
    __syncthreads();
    if (threadIdx.x == 0) {
        atomicMax(v_max, local_max);
    }
}

// encontra a soma dos produtos escalares das linhas
__global__ void dot_kernel(int *a, int *b, int n, int *dot) {
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < n * n) {
        int i = index / n;
        atomicAdd(&dot[i], a[index] * b[index]);
    }
}

//  soma os elementos de dot para dot[0]
__global__ void dot_sum_kernel(int *dot, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i > 0 && i < n) {
        atomicAdd(&dot[0], dot[i]);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Por favor, insira o arquivo a ser lido.");
        return -1;
    }

    FILE* input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Arquivo invalido.");
        return -1;
    }

    int n; // dimensao da matriz
    fscanf(input, "%d", &n);

    int N = n * n; // tamanho total

    int* a = (int*) malloc(N * sizeof(int));
    int* b = (int*) malloc(N * sizeof(int));

    // read matrix A
    for (int i = 0; i < N; i++) {
        fscanf(input, "%d", &a[i]);
    }

    // read matrix B
    for (int i = 0; i < N; i++) {
        fscanf(input, "%d", &b[i]);
    }

    // fecha o arquivo de entrada
    fclose(input);

    // -------------- fim da entrada -------------------------

    // inicializa os vetores CUDA
    int *a_cuda, *b_cuda;
    cudaMalloc(&a_cuda, N * sizeof(int));
    cudaMalloc(&b_cuda, N * sizeof(int));
    
    cudaMemcpy(a_cuda, a, N * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(b_cuda, b, N * sizeof(int), cudaMemcpyHostToDevice);
    
    // inicializa os vetores de resposta
    int *min, *max, *dot;
    cudaMallocHost(&min, sizeof(int));
    cudaMallocHost(&max, sizeof(int));
    cudaMallocHost(&dot, n * sizeof(int)); // um pra cada linha
    
    *min = *max = a[0];
    for (int i = 0; i < n; i++) {
        dot[i] = 0;
    }
    
    // aloca vetores das respostas na GPU
    int *min_cuda, *max_cuda, *dot_cuda;
    cudaMalloc(&min_cuda, sizeof(int));
    cudaMalloc(&max_cuda, sizeof(int));
    cudaMalloc(&dot_cuda, n * sizeof(int));
    
    // cria as streams para cada operacao
    cudaStream_t min_stream, max_stream, dot_stream;
    cudaStreamCreate(&min_stream);
    cudaStreamCreate(&max_stream);
    cudaStreamCreate(&dot_stream);
    
    // colocando as operaceos de copia nas streams
    cudaMemcpyAsync(min_cuda, min, sizeof(int), cudaMemcpyHostToDevice, min_stream);
    cudaMemcpyAsync(max_cuda, max, sizeof(int), cudaMemcpyHostToDevice, max_stream);
    cudaMemcpyAsync(dot_cuda, dot, n * sizeof(int), cudaMemcpyHostToDevice, dot_stream);
    
    // chama os kernels de min
    min_kernel<<<(N + BLOCK_SIZE - 1) / BLOCK_SIZE, BLOCK_SIZE, 0, min_stream>>>(a_cuda, N, min_cuda);
    min_kernel<<<(N + BLOCK_SIZE - 1) / BLOCK_SIZE, BLOCK_SIZE, 0, min_stream>>>(b_cuda, N, min_cuda);
    
    // chama os kernels de max
    max_kernel<<<(N + BLOCK_SIZE - 1) / BLOCK_SIZE, BLOCK_SIZE, 0, max_stream>>>(a_cuda, N, max_cuda);
    max_kernel<<<(N + BLOCK_SIZE - 1) / BLOCK_SIZE, BLOCK_SIZE, 0, max_stream>>>(b_cuda, N, max_cuda);
    
    // chama os kernels de produto escalar
    dot_kernel<<<(N + BLOCK_SIZE - 1) / BLOCK_SIZE, BLOCK_SIZE, 0, dot_stream>>>(a_cuda, b_cuda, n, dot_cuda);

    // chama os kernels de somar os produtos escalares
    dot_sum_kernel<<<(n + BLOCK_SIZE - 1) / BLOCK_SIZE, BLOCK_SIZE, 0, dot_stream>>>(dot_cuda, n);
    
    // copia as respostas de volta
    cudaMemcpyAsync(min, min_cuda, sizeof(int), cudaMemcpyDeviceToHost, min_stream);
    cudaMemcpyAsync(max, max_cuda, sizeof(int), cudaMemcpyDeviceToHost, max_stream);
    cudaMemcpyAsync(dot, dot_cuda, n * sizeof(int), cudaMemcpyDeviceToHost, dot_stream);
    
    // sincroniza as streams
    cudaStreamSynchronize(min_stream);
    cudaStreamSynchronize(max_stream);
    cudaStreamSynchronize(dot_stream);
    
    // destroi as streams
    cudaStreamDestroy(min_stream);
    cudaStreamDestroy(max_stream);
    cudaStreamDestroy(dot_stream);
    
    // imprime a resposta
    printf("%d %d %d\n", dot[0], *min, *max);
    
    // libera as memorias utilizadas
    free(a);
    free(b);
    
    cudaFree(a_cuda);
    cudaFree(b_cuda);
    cudaFree(min_cuda);
    cudaFree(max_cuda);
    cudaFree(dot_cuda);
    
    cudaFreeHost(min);
    cudaFreeHost(max);
    cudaFreeHost(dot);

    return 0;
}
