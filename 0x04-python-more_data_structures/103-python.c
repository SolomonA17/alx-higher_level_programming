#include <Python.h>
#include <listobject.h>
#include <object.h>
#include <bytesobject.h>

/**
 * print_python_bytes - Prints information about a Python byte object
 *
 * Description: This function prints various information about a Python byte object,
 * including its size, a string representation, and the first 10 bytes in hexadecimal
 * format.
 *
 * @p: PyObject pointer to the byte object
 *
 * Return: void
 */
void print_python_bytes(PyObject *p) {
    long int size_of_bytes, i;

    printf("[.] Byte object information\n");

    if (PyBytes_CheckExact(p)) {
        size_of_bytes = PyBytes_Size(p);
        printf("    Size: %ld\n", size_of_bytes);
        printf("    String representation: %s\n", PyBytes_AsString(p));

        // Print the first 10 bytes in hexadecimal format
        if (size_of_bytes >= 10) {
            size_of_bytes = 10;
        } else {
            size_of_bytes++;
        }

        printf("    First %ld bytes: ", size_of_bytes);

        for (i = 0; i < size_of_bytes; i++) {
            printf(" %02x", (int) PyBytes_AsString(p)[i] & 0xff);
        }

        printf("\n");
    } else {
        printf("    [ERROR] Invalid byte object\n");
    }
}

/**
 * print_python_list - Prints information about a Python list
 *
 * Description: This function prints various information about a Python list,
 * including its size, allocated memory, and the type and string representation of
 * each element. For elements that are byte objects, it also prints the first 10
 * bytes in hexadecimal format.
 *
 * @p: PyObject pointer to the list object
 *
 * Return: void
 */
void print_python_list(PyObject *p) {
    long int size_of_list = PyList_GET_SIZE(p), list_index;
    PyObject *temp;
    PyListObject *list_object = (PyListObject *) p;

    printf("[*] Python list information\n");
    printf("[*] Size of the Python list = %ld\n", size_of_list);
    printf("[*] Allocated = %ld\n", list_object->allocated);

    // Iterate through the list elements
    for (list_index = 0; list_index < size_of_list; list_index++) {
        temp = PyList_GET_ITEM(p, list_index);

        // Print the element index and type
        printf("    Element %ld: %s\n", list_index, temp->ob_type->tp_name);

        // If the element is a byte object, print its details
        if (PyBytes_CheckExact(temp)) {
            print_python_bytes(temp);
        }
    }
}
