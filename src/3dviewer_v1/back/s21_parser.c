/*!
\file
\brief Исходный файл, содержащий функции для парсинга obj-файла, обработки и
структурирования считанной информации, а так же всппомогательные функции.

*/
#include "s21_3dviewer.h"

int obj_file_full(char *filename, vertexes *vertex_arr, polygons *polygon_arr) {
  vertex maxes = {0, 0, 0};
  vertex mins = {0, 0, 0};
  double value_scale = 0.5;
  if (obj_file_parser(filename, vertex_arr, polygon_arr) != SUCCESS)
    return FAILURE;
  max_min_vertex(vertex_arr, &maxes, &mins);
  rescaling_and_centering(vertex_arr, maxes, mins, value_scale);

  return SUCCESS;
}

int obj_file_parser(char *filename, vertexes *vertex_arr,
                    polygons *polygon_arr) {
  int out = SUCCESS;
  int length = MAX_LEN;
  char string_from_file[length];
  int point_parser_result = SUCCESS;
  int surface_parser_result = SUCCESS;
  int points_quantity = 0;
  int surfaces_quantity = 0;
  int edges_quantity = 0;
  int i = 0;
  int j = 0;
  FILE *file_3d = fopen(filename, "r+");
  if (file_3d == NULL) return FAILURE;
  obj_points_surfaces_counter(file_3d, &points_quantity, &surfaces_quantity);
  if (create_vertex_polygon(points_quantity, vertex_arr, surfaces_quantity,
                            polygon_arr) != SUCCESS)
    return FAILURE;
  rewind(file_3d);

  while (fgets(string_from_file, length, file_3d) != NULL) {
    point_parser_result = point_parser(string_from_file, vertex_arr->vert + i);
    if (point_parser_result == SUCCESS) i++;

    surface_parser_result = surface_parser(
        string_from_file, polygon_arr->polygon + j, &(edges_quantity));
    if (surface_parser_result == SUCCESS) j++;
  }
  polygon_arr->amount_edges = edges_quantity / 2;
  if (fclose(file_3d) != 0) return FAILURE;
  return out;
}

void obj_points_surfaces_counter(FILE *file_3d, int *result_points,
                                 int *result_surfaces) {
  int out = SUCCESS;
  int length = MAX_LEN;
  char string_from_file[length];
  ;
  while (fgets(string_from_file, length, file_3d) != NULL) {
    if (*string_from_file == 'v' && *(string_from_file + 1) == ' ')
      (*result_points)++;
    if (*string_from_file == 'f' && *(string_from_file + 1) == ' ')
      (*result_surfaces)++;
  }
}

int create_vertex_polygon(int amount_v, vertexes *result_v, int amount_p,
                          polygons *result_p) {
  if (result_v == NULL || result_p == NULL) return FAILURE;
  if (amount_v <= 3 || amount_p <= 1) return FAILURE;
  result_v->p_amount = amount_v;
  result_p->amount_poly = amount_p;
  result_v->vert = calloc(result_v->p_amount, sizeof(vertex));
  result_p->polygon = calloc(result_p->amount_poly, sizeof(polygon));
  return SUCCESS;
}

int point_parser(char *readed_string, vertex *point) {
  if (*readed_string != 'v') return WRONG_TYPE;

  char ch = 0;
  if (sscanf(readed_string, "%c %lf %lf %lf", &ch, &(point->x), &(point->y),
             &(point->z)) != 4)
    return FAILURE;
  return SUCCESS;
}

int surface_parser(char *readed_string, polygon *poly, int *amount_edges) {
  if (*readed_string != 'f') return FAILURE;
  int str_len = (int)strlen(readed_string);
  char *tmp_string = calloc(str_len, sizeof(char));

  poly->amount_points = push_to_tmp_str(readed_string, tmp_string, str_len) + 1;
  *amount_edges += poly->amount_points;
  poly->points = calloc(poly->amount_points, sizeof(int));
  forming_polygon(tmp_string, poly->points);

  free(tmp_string);
  return SUCCESS;
}

void forming_polygon(char *tmp_str, int *p_arr) {
  int len = (int)strlen(tmp_str);
  char *substr = calloc(len, sizeof(char));
  int out = 0;
  int j = 0;
  int k = 0;
  for (size_t i = 0; i < len; i++) {
    if (isdigit(tmp_str[i]) != 0) {
      substr[j] = tmp_str[i];
      j++;
    }
    if (tmp_str[i] == ' ' || tmp_str[i] == '#') {
      *(p_arr + k) = atoi(substr) - 1;
      strclean(substr, j);
      j = 0;
      k++;
    }
  }
  free(substr);
}

void strclean(char *str, int j) {
  for (int i = 0; i < j; i++) {
    if (isdigit(str[i]) != 0) str[i] = '\0';
  }
}

int push_to_tmp_str(char *read_str, char *tmp_str, int len) {
  int j = 0;
  int push_allowed = 1;
  int out = 0;

  for (size_t i = 2; i < len; i++) {
    if (read_str[i] == ' ') {
      push_allowed = 1;
      out++;
      tmp_str[j] = read_str[i];
      j++;
    }
    if (isdigit(read_str[i]) != 0 && push_allowed == 1) {
      tmp_str[j] = read_str[i];
      j++;
    }
    if (read_str[i] == '/') push_allowed = 0;
  }
  tmp_str[j] = '#';
  return out;
}

int vertexcopy(vertexes *arr_v_1, vertexes *arr_v_2) {
  if (arr_v_1 == NULL || arr_v_2 == NULL) return FAILURE;
  arr_v_2->p_amount = arr_v_1->p_amount;
  arr_v_2->vert = calloc(arr_v_2->p_amount, sizeof(vertex));
  if (arr_v_2->vert == NULL) return FAILURE;
  vertex *pp_1 = arr_v_1->vert;
  vertex *pp_2 = arr_v_2->vert;

  for (int i = 1; i <= arr_v_1->p_amount; i++, pp_1++, pp_2++) {
    *pp_2 = *pp_1;
  }

  return SUCCESS;
}

void print_points_polygons(vertexes *arr_v, polygons *arr_p) {
  vertex *pp = arr_v->vert;
  polygon *polyp = arr_p->polygon;
  for (int i = 1; i <= arr_v->p_amount; i++, pp++) {
    printf("\nPoint number = %d from %d\nX = %lf\nY = %lf\nZ = %lf\n\n", i,
           arr_v->p_amount, pp->x, pp->y, pp->z);
  }

  for (int i = 1; i <= arr_p->amount_poly; i++, polyp++) {
    printf("\nPolygon number = %d from %d\n", i, arr_p->amount_poly);

    for (int j = 0; j < polyp->amount_points; j++) {
      printf("Point %d = %d\n", j, *(polyp->points + j));
    }
  }
}

void max_min_vertex(vertexes *arr_v, vertex *max_xyz, vertex *min_xyz) {
  vertex *pp = arr_v->vert;
  max_xyz->x = pp->x;
  max_xyz->y = pp->y;
  max_xyz->z = pp->z;

  min_xyz->x = pp->x;
  min_xyz->y = pp->y;
  min_xyz->z = pp->z;

  for (int i = 1; i <= arr_v->p_amount; i++, pp++) {
    if (max_xyz->x <= pp->x) max_xyz->x = pp->x;
    if (max_xyz->y <= pp->y) max_xyz->y = pp->y;
    if (max_xyz->z <= pp->z) max_xyz->z = pp->z;

    if (min_xyz->x >= pp->x) min_xyz->x = pp->x;
    if (min_xyz->y >= pp->y) min_xyz->y = pp->y;
    if (min_xyz->z >= pp->z) min_xyz->z = pp->z;
  }
}

void rescaling_and_centering(vertexes *arr_v, vertex max_xyz, vertex min_xyz,
                             double value_scale) {
  vertex center_xyz = {0, 0, 0};
  vertex diff_max_min = {0, 0, 0};
  vertex *pp = arr_v->vert;
  diff_max_min.x = max_xyz.x - min_xyz.x;
  diff_max_min.y = max_xyz.y - min_xyz.y;
  diff_max_min.z = max_xyz.z - min_xyz.z;

  double max_diff = fmax(fmax(diff_max_min.x, diff_max_min.y), diff_max_min.z);

  double scal = (value_scale + value_scale) / max_diff;
  center_xyz.x = min_xyz.x + (max_xyz.x - min_xyz.x) / 2;
  center_xyz.y = min_xyz.y + (max_xyz.y - min_xyz.y) / 2;
  center_xyz.z = min_xyz.z + (max_xyz.z - min_xyz.z) / 2;

  for (int i = 0; i < arr_v->p_amount; i++, pp++) {
    pp->x -= center_xyz.x;
    pp->y -= center_xyz.y;
    pp->z -= center_xyz.z;

    pp->x *= scal;
    pp->y *= scal;
    pp->z *= scal;
  }
}
