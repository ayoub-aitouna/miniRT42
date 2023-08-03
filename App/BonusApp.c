/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BonusApp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 20:15:55 by clyamani          #+#    #+#             */
/*   Updated: 2023/08/03 22:02:09 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/bonus/parsing/headers/bonousparsing.h"
#include "../src/headers/image.h"
#include "../src/headers/main.h"
#include "../src/headers/scene.h"
#include "../src/headers/types.h"
#include "../src/parsing/headers/parsing.h"

t_list	*parse_scene(char *file_name)
{
	return (bns_readfile(file_name));
}
