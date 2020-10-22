# gprof


- Primeiramente tem q compilar com -pg

```gcc A.c -o A -pg```

- Depois executa uma vez

```./A```

- Depois, deve ter criado um arquivo gmon.out, agora executa o gprof:

```gprof ./A gmon.out```

- Se tiver os pythons, faz o seguinte, pode gerar o out e dps gerar o png