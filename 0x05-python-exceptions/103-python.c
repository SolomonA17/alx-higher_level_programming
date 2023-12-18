#include <stdio.h>
#include <Python.h>

/**
 * Print information about a Python bytes object.
 *
 * @param py_object The Python object to analyze.
 */
void print_python_bytes_info(PyObject *py_object) {
  char *byte_string;
  Py_ssize_t byte_size, i, limit;

  // Disable buffering for immediate output.
  setbuf(stdout, NULL);

  printf("[*] Byte object details:\n");
  if (!PyBytes_Check(py_object)) {
    printf("  [ERROR] Invalid bytes object.\n");
    setbuf(stdout, NULL);
    return;
  }

  byte_size = Py_SIZE(py_object);
  byte_string = PyBytes_AsString(py_object);

  printf("  * Size: %zd\n", byte_size);
  printf("  * First %zd bytes:", limit = (byte_size > 10) ? 10 : byte_size + 1);

  for (i = 0; i < limit; i++) {
    if (byte_string[i] >= 0) {
      printf(" %02x", byte_string[i]);
    } else {
      printf(" %02x", 256 + byte_string[i]);
    }
  }

  printf("\n");
  setbuf(stdout, NULL);
}

/**
 * Print information about a Python float object.
 *
 * @param py_object The Python object to analyze.
 */
void print_python_float_info(PyObject *py_object) {
  double float_value;
  char *formatted_string;

  // Disable buffering for immediate output.
  setbuf(stdout, NULL);

  printf("[*] Float object details:\n");
  if (!PyFloat_Check(py_object)) {
    printf("  [ERROR] Invalid float object.\n");
    setbuf(stdout, NULL);
    return;
  }

  float_value = PyFloat_AsDouble(py_object);
  formatted_string = PyOS_double_to_string(float_value, 'r', 0, Py_DTSF_ADD_DOT_0, Py_DTST_FINITE);

  printf("  * Value: %s\n", formatted_string);
  PyMem_Free(formatted_string);
  setbuf(stdout, NULL);
}

/**
 * Print information about a Python list object.
 *
 * @param py_object The Python object to analyze.
 */
void print_python_list_info(PyObject *py_object) {
  Py_ssize_t element_count, index;
  PyObject *list_item;
  PyListObject *py_list = (PyListObject *)py_object;

  // Disable buffering for immediate output.
  setbuf(stdout, NULL);

  printf("[*] Python list information:\n");
  if (!PyList_Check(py_object)) {
    printf("  [ERROR] Invalid list object.\n");
    setbuf(stdout, NULL);
    return;
  }

  element_count = Py_SIZE(py_object);
  printf("  * Size: %zd\n", element_count);
  printf("  * Allocated: %zd\n", py_list->allocated);

  for (index = 0; index < element_count; index++) {
    list_item = py_list->ob_item[index];
    printf("  * Element %zd: %s\n", index, Py_TYPE(list_item)->tp_name);

    if (PyBytes_Check(list_item)) {
      print_python_bytes_info(list_item);
    } else if (PyFloat_Check(list_item)) {
      print_python_float_info(list_item);
    }
  }

  setbuf(stdout, NULL);
}

