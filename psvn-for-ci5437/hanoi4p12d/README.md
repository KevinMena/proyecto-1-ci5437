## Compilar

Para compilar los pdb, se corren los comando  
```
make -f make_pdb.mk hanoi4p12d/abst_1.pdb
make -f make_pdb.mk hanoi4p12d/abst_2.pdb
make -f make_pdb.mk hanoi4p12d/abst_3.pdb
make -f make_solver.mk hanoi4p12d.ida_star
make -f make_solver.mk hanoi4p12d.a_star
```

## Correr el algoritmo

```
./hanoi4p12d.<algoritmo> <path_archivo_entrada> <path_archivo_salida>
```