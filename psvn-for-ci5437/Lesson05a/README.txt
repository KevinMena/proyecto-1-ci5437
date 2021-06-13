Para crear PDB test.pdb para el problema hanoi3_5d.psvn, ejecutar:

make hanoi3_5d/test.pdb

Asume que test.txt existe y contiene los comandos para
el abstractor que generan la abstraccion deseada.

Si quieren ver los valores que da la abstraccion sobre el
problema original, construir .dist_pdb y ejecutarlo.
Por ejemplo,

make hanoi3_5d.dist_pdb
./hanoi3_5d.dist_pdb test

Para ver como utilizar las PDB en algoritmo de busqueda ver
global/dist_pdb.cpp. En particular, para calcular el valor
para un estado, hacer:

    // compute PDB value for state
    state_t abst_state;
    abstract_state(abst, &state, &abst_state);
    const int *pdb_value = state_map_get(pdb, &abst_state);
    assert(pdb_value != 0);
    int value = *pdb_value;

donde abst es un apuntador a abstraction_t, y pdb
es un apuntador a state_map_t.

