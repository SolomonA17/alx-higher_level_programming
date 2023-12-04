#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <listobject.h>
#include <object.h>

/**
 * print_python_list_info - Uncover essential information about Python lists
 *
 * Description: This function unveils the size, allocated memory, and data types of a given Python list.
 *
 * Arguments: p (PyObject): The Python list object to be analyzed
 *
 * Returns: None
 */

void print_python_list_info(PyObject *p)
{
	long int size_of_list = Py_SIZE(p), list_index;
	PyListObject *list_object = (PyListObject *) p;

	printf("[*] Size of the Python List = %ld\n", size_of_list);
	printf("[*] Allocated = %ld\n", list_object->allocated);

	for (list_index = 0; list_index < size_of_list; list_index++)
		printf("Element %ld: %s\n", list_index,
				Py_TYPE(PyList_GetItem(p, list_index))->tp_name);
}
