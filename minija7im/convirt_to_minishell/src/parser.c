/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:29:43 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/21 19:50:01 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

// #include <stdio.h>

// typedef struct s_list
// {
//         char*                   name;
//         int                             age;
//         struct s_list*  previous;
//         struct s_list*  next;
// } t_list;

// t_list  assing_data(char* name, int age, t_list *previous, t_list *next)
// {
//         t_list  student;

//         student.name = name;
//         student.age = age;
//         student.previous = previous;
//         student.next = next;

//         return (student);
// }

// int     main(void)
// {

//         t_list  student1;
//         t_list  student2;
//         struct s_list   *test;


//         student1 = assing_data("Rahhal", 25, NULL, &student2);
//         student2 = assing_data("Rizqy", 30, &student1, NULL);

//         test = student1.next;
//         printf("%s\n", test->name);

//         return (0);
// }