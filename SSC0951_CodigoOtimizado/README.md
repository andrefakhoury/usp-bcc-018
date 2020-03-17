# Desenvolvimento de Código Otimizado

- Prof Sarita

## Packages para instalar

- `linux-tools-common`
- `linux-tools-generic`

## Comando

`sudo perf stat -e L1-dcache-loads,L1-dcache-load-misses ./program`

# Relembrando termos importantes

- **ILP:** Instruction Level Paralelism
- **ICP:** Instruction per Clock
- **CPI:** Clock per Instruction
- **Pipeline:** Execução paralela de instruções
  - Problemas: dependência de dados, controle
  - Gargalos: acesso à memória (cache)
    - Desvios: prediction