## Compilar

Para compilar los pdb, se corren los comando  
```
make -f make_pdb.mk hanoi4p14d/abst_1.pdb
make -f make_pdb.mk hanoi4p14d/abst_2.pdb
make -f make_pdb.mk hanoi4p14d/abst_3.pdb
make -f make_solver.mk hanoi4p14d.ida_star
make -f make_solver.mk hanoi4p14d.a_star
```

## Correr el algoritmo

```
./hanoi4p14d.<algoritmo> <path_archivo_entrada> <path_archivo_salida>
```