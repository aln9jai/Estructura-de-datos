#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dlist.h"

/*
   Print List
*/

static void print_list (const DList *list) {
    DListNode *node;
    int *data, i;

    fprintf(stdout, "DList size is %d\n", dlist_size(list));

    i = 0;
    node = dlist_head(list);

    while (1) {
        data = dlist_data(node);
        fprintf(stdout, "dlist.node[%03d]=%03d, %14p <- %p -> %p \n", i, *data, node->prev, node, node->next);

        i++;

        if (dlist_is_tail(node))
            break;
        else
            node = dlist_next(node);
    }

   return;
}

/*
*/
static void show_usage(const char *program_name) {
    fprintf(stderr, "Uso: %s <numero1> <numero2> <numero3> ...\n", program_name);
}

int main (int argc, char **argv) {
    DList list;
    DListNode *node;
    int *data, i;

    
    if (argc < 2) {
        show_usage(argv[0]);
        fprintf(stderr, "Error: Se requieren numeros como argumentos.\n");
        return 1;
    }

    
    dlist_init(&list, free);

    fprintf(stdout, "=== Creando lista doblemente ligada con %d elementos ===\n", argc - 1);

    
    for (i = 1; i < argc; i++) {
        
        int value = atoi(argv[i]);
        
        if ((data = (int *)malloc(sizeof(int))) == NULL) {
            fprintf(stderr, "Error: No se pudo asignar memoria para el elemento %d\n", i);
            dlist_destroy(&list);
            return 1;
        }

        *data = value;

        if (dlist_ins_next(&list, dlist_tail(&list), data) != 0) {
            fprintf(stderr, "Error: No se pudo insertar el elemento %d: %d\n", i, value);
            free(data);
            dlist_destroy(&list);
            return 1;
        }
        
        fprintf(stdout, "Insertado: %d\n", value);
    }

    fprintf(stdout, "\n=== Lista inicial creada desde linea de comandos ===\n");
    print_list(&list);

    // === Operaciones de demostración ===

    fprintf(stdout, "\n=== Avanzando al 3er nodo (si existe) ===\n");
    node = dlist_head(&list);
    
    if (node != NULL && dlist_next(node) != NULL && dlist_next(dlist_next(node)) != NULL) {
        for (i = 0; i < 2 && node != NULL; ++i)
            node = dlist_next(node);
        
        if (node != NULL) {
            data = dlist_data(node);
            fprintf(stdout, "Nodo actual: %03d\n", *data);
            
            fprintf(stdout, "\nRemoving a node after the one containing %03d\n", *data);
            if (dlist_remove(&list, node, (void**)&data) != 0) {
                fprintf(stderr, "Error eliminando nodo\n");
            } else {
                fprintf(stdout, "Elemento eliminado: %03d\n", *data);
                print_list(&list);

                fprintf(stdout, "\nInserting 187 at the tail of the list\n");
                *data = 187;
                if (dlist_ins_next(&list, dlist_tail(&list), data) != 0) {
                    fprintf(stderr, "Error insertando 187\n");
                    free(data);
                } else {
                    print_list(&list);
                }
            }
        }
    } else {
        fprintf(stdout, "La lista es demasiado corta para esta operación\n");
    }

    if (dlist_size(&list) > 0) {
        fprintf(stdout, "\nRemoving a node at the tail of the list\n");
        if (dlist_remove(&list, dlist_tail(&list), (void**)&data) != 0) {
            fprintf(stderr, "Error eliminando la cola\n");
        } else {
            fprintf(stdout, "Elemento eliminado: %03d\n", *data);
            print_list(&list);

            fprintf(stdout, "\nInsert 975 before the tail of the list\n");
            *data = 975;
            if (dlist_ins_prev(&list, dlist_tail(&list), data) != 0) {
                fprintf(stderr, "Error insertando 975\n");
                free(data);
            } else {
                print_list(&list);
            }
        }
    }

    if (dlist_size(&list) >= 5) {
        fprintf(stdout, "\nIterating and removing the fifth node\n");
        node = dlist_head(&list);
        
        for (i = 0; i < 4 && node != NULL; i++) {
            node = dlist_next(node);
        }
        
        if (node != NULL) {
            if (dlist_remove(&list, node, (void **)&data) != 0) {
                fprintf(stderr, "Error eliminando el quinto nodo\n");
            } else {
                fprintf(stdout, "Elemento eliminado: %03d\n", *data);
                print_list(&list);
            }
        }
    }

    if (dlist_size(&list) > 0) {
        fprintf(stdout, "\nInserting 607 before the head node\n");
        if ((data = (int *)malloc(sizeof(int))) == NULL) {
            fprintf(stderr, "Error asignando memoria para 607\n");
        } else {
            *data = 607;
            if (dlist_ins_prev(&list, dlist_head(&list), data) != 0) {
                fprintf(stderr, "Error insertando 607\n");
                free(data);
            } else {
                print_list(&list);
            }
        }
    }
    
    // Eliminar cabeza
    if (dlist_size(&list) > 0) {
        fprintf(stdout, "\nRemoving a node at the head of the list\n");
        if (dlist_remove(&list, dlist_head(&list), (void**)&data) != 0) {
            fprintf(stderr, "Error eliminando la cabeza\n");
        } else {
            fprintf(stdout, "Elemento eliminado: %03d\n", *data);
            print_list(&list);

            fprintf(stdout, "\nInserting 900 after the head node\n");
            *data = 900;
            if (dlist_ins_next(&list, dlist_head(&list), data) != 0) {
                fprintf(stderr, "Error insertando 900\n");
                free(data);
            } else {
                print_list(&list);
            }
        }
    }

    // Insertar dos nodos después de la cabeza
    if (dlist_size(&list) >= 2) {
        fprintf(stdout, "\nInserting 080 two nodes after the head of the list\n");
        if ((data = (int *)malloc(sizeof(int))) == NULL) {
            fprintf(stderr, "Error asignando memoria para 080\n");
        } else {
            *data = 80;
            node = dlist_head(&list);
            node = dlist_next(node);
            if (dlist_ins_next(&list, node, data) != 0) {
                fprintf(stderr, "Error insertando 080\n");
                free(data);
            } else {
                print_list(&list);
            }
        }
    }

    if (dlist_size(&list) > 0) {
        i = dlist_is_head(dlist_head(&list));
        fprintf(stdout, "Testing dlist_is_head... value=%d (1=OK)\n", i);
        i = dlist_is_head(dlist_tail(&list));
        fprintf(stdout, "Testing dlist_is_head... value=%d (0=OK)\n", i);
        i = dlist_is_tail(dlist_tail(&list));
        fprintf(stdout, "Testing dlist_is_tail... value=%d (1=OK)\n", i);
        i = dlist_is_tail(dlist_head(&list));
        fprintf(stdout, "Testing dlist_is_tail... value=%d (0=OK)\n", i);
    } else {
        fprintf(stdout, "Lista vacía - no se pueden realizar pruebas de verificación\n");
    }

    fprintf(stdout, "\nDestroying the list\n");
    dlist_destroy(&list);
    fprintf(stdout, "Lista destruida exitosamente.\n");

    return 0;
}
