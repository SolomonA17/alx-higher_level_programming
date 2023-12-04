#include "lists.h"

listint_t *reverse_listint(listint_t **head);
int is_palindrome(listint_t **head);

/**
 * Reverses a singly-linked listint_t list.
 * @head: A pointer to the starting node of the list to reverse.
 *
 * Return: A pointer to the head of the reversed list.
 */

listint_t *reverse_listint(listint_t **head)
{
    // This function reverses a singly-linked list by maintaining three pointers:
    // node: The current node being processed
    // next: The next node after the current node
    // prev: The previously processed node

    listint_t *node = *head, *next, *prev = NULL;

    while (node)  // Iterate through the list
    {
        next = node->next;  // Save the next node
        node->next = prev;  // Link the current node to the previously processed node
        prev = node;        // Update the previously processed node to the current node
        node = next;        // Move to the next node
    }

    *head = prev;  // Update the head of the list to the last node
    return (*head);  // Return the head of the reversed list
}

/**
 * Checks if a singly linked list is a palindrome.
 * @head: A pointer to the head of the linked list.
 *
 * Return: If the linked list is not a palindrome - 0.
 *     If the linked list is a palindrome - 1.
 */
int is_palindrome(listint_t **head)
{
    // This function checks if a singly-linked list is a palindrome by reversing the second half of the list and comparing it to the first half.

    listint_t *tmp, *rev, *mid;  // Declare temporary pointers
    size_t size = 0, i;           // Declare variables for size and index

    if (*head == NULL || (*head)->next == NULL)  // Check if the list is empty or has only one node
        return (1);  // If so, it is a palindrome

    // Count the number of nodes in the list
    tmp = *head;
    while (tmp)
    {
        size++;
        tmp = tmp->next;
    }

    // Find the middle node
    tmp = *head;
    for (i = 0; i < (size / 2) - 1; i++)
        tmp = tmp->next;

    // If the size is odd, skip the middle node
    if ((size % 2) == 0 && tmp->n != tmp->next->n)
        return (0);

    // Reverse the second half of the list
    tmp = tmp->next->next;
    rev = reverse_listint(&tmp);
    mid = rev;

    // Compare the first half to the reversed second half
    tmp = *head;
    while (rev)
    {
        if (tmp->n != rev->n)
            return (0);
        tmp = tmp->next;
        rev = rev->next;
    }

    // Restore the second half of the list
    reverse_listint(&mid);

    return (1);
}
