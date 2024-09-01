/*!
\file
\brief Исходный файл, содержащий функции для реализации базовых преобразований
3D-модели: перемещения, вращения, масштабирования.

*/
#include "s21_3dviewer.h"

void transformation(vertexes *v_arr, transformation_t type,
                    axis_values *values) {
  vertex *pp = v_arr->vert;
  for (int i = 1; i <= v_arr->p_amount; i++, pp++) {
    if (type == translation) {
      matrix_translation(pp, values);
    } else if (type == rotation) {
      matrix_rotation(pp, values);
    } else if (type == scaling) {
      matrix_scaling(pp, values);
    }
  }
}

void matrix_translation(vertex *point, axis_values *trans_values) {
  point->x += trans_values->x_axis;
  point->y += trans_values->y_axis;
  point->z += trans_values->z_axis;
}

void matrix_rotation(vertex *point, axis_values *rot_values) {
  if (rot_values->x_axis != 0) rotation_x(point, rot_values);
  if (rot_values->y_axis != 0) rotation_y(point, rot_values);
  if (rot_values->z_axis != 0) rotation_z(point, rot_values);
}

void rotation_x(vertex *point, axis_values *rot_values) {
  double rotation_varr[3] = {point->x, point->y, point->z};
  double rotation_varr_new[3] = {0.0000000, 0.0000000, 0.0000000};
  double degrees = rot_values->x_axis * (PI / 180.0000000);

  point->y = rotation_varr[1] * cos(degrees) - rotation_varr[2] * sin(degrees);
  point->z = rotation_varr[1] * sin(degrees) + rotation_varr[2] * cos(degrees);
}

void rotation_y(vertex *point, axis_values *rot_values) {
  double rotation_varr[3] = {point->x, point->y, point->z};
  double degrees = rot_values->y_axis * (PI / 180.0000000);

  point->x = rotation_varr[0] * cos(degrees) + rotation_varr[2] * sin(degrees);
  point->z = -rotation_varr[0] * sin(degrees) + rotation_varr[2] * cos(degrees);
}

void rotation_z(vertex *point, axis_values *rot_values) {
  double rotation_varr[3] = {point->x, point->y, point->z};
  double degrees = rot_values->z_axis * (PI / 180.0000000);

  point->x = rotation_varr[0] * cos(degrees) - rotation_varr[1] * sin(degrees);
  point->y = rotation_varr[0] * sin(degrees) + rotation_varr[1] * cos(degrees);
}

void matrix_scaling(vertex *point, axis_values *scale_values) {
  point->x *= scale_values->x_axis;
  point->y *= scale_values->y_axis;
  point->z *= scale_values->z_axis;
}
