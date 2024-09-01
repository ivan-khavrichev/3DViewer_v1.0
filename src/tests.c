/*!
\file
\brief Исходный файл, содержащий код для тестирования корректности работы
основных функций.

Требуемое покрытие - 80%.
*/
#include <check.h>

#include "3dviewer_v1/back/s21_3dviewer.h"

START_TEST(simple_test_1) {
  char *filename = "models/truncated-tetrahedron.obj";

  vertexes vertex_arr = {0, 0};
  polygons polygon_arr = {0, 0, 0};
  vertexes vertex_arr_answer = {0, 0};
  polygons polygon_arr_answer = {0, 0, 0};
  vertex maxs_a = {0, 0, 0};
  vertex mins_a = {0, 0, 0};
  vertex_arr_answer.p_amount = 12;
  polygon_arr_answer.amount_poly = 20;
  polygon_arr_answer.amount_edges = 30;
  create_vertex_polygon(12, &vertex_arr_answer, 20, &polygon_arr_answer);
  vertex *pp_a = vertex_arr_answer.vert;
  polygon *polyp = polygon_arr_answer.polygon;

  (pp_a + 0)->x = 1.6666666;
  (pp_a + 0)->y = 5.552925;
  (pp_a + 0)->z = 7.5426464;

  (pp_a + 1)->x = 3.3333333;
  (pp_a + 1)->y = 2.6661737;
  (pp_a + 1)->z = 7.5426464;

  (pp_a + 2)->x = 1.6664362;
  (pp_a + 2)->y = 3.6282907;
  (pp_a + 2)->z = 10.264490;

  (pp_a + 3)->x = 3.3335638;
  (pp_a + 3)->y = 4.5908065;
  (pp_a + 3)->z = 12.987463;

  (pp_a + 4)->x = 8.3335640;
  (pp_a + 4)->y = 3.6282907;
  (pp_a + 4)->z = 10.26449;

  (pp_a + 5)->x = 6.6666665;
  (pp_a + 5)->y = 2.6661737;
  (pp_a + 5)->z = 7.5426464;

  (pp_a + 6)->x = 6.6664360;
  (pp_a + 6)->y = 4.5908065;
  (pp_a + 6)->z = 12.987463;

  (pp_a + 7)->x = 5.0000000;
  (pp_a + 7)->y = 9.402193;
  (pp_a + 7)->z = 10.26449;

  (pp_a + 8)->x = 6.6666665;
  (pp_a + 8)->y = 8.439676;
  (pp_a + 8)->z = 7.5426464;

  (pp_a + 9)->x = 3.3333333;
  (pp_a + 9)->y = 8.439676;
  (pp_a + 9)->z = 7.5426464;

  (pp_a + 10)->x = 8.3333330;
  (pp_a + 10)->y = 5.552925;
  (pp_a + 10)->z = 7.5426464;

  (pp_a + 11)->x = 5.0000000;
  (pp_a + 11)->y = 7.477159;
  (pp_a + 11)->z = 12.987463;
  for (size_t i = 0; i < 20; i++) {
    (polyp + i)->points = calloc(3, sizeof(int));
    (polyp + i)->amount_points = 3;
  }
  (polyp + 0)->points[0] = 0;
  (polyp + 0)->points[1] = 1;
  (polyp + 0)->points[2] = 2;

  (polyp + 1)->points[0] = 3;
  (polyp + 1)->points[1] = 2;
  (polyp + 1)->points[2] = 4;

  (polyp + 2)->points[0] = 4;
  (polyp + 2)->points[1] = 2;
  (polyp + 2)->points[2] = 1;

  (polyp + 3)->points[0] = 4;
  (polyp + 3)->points[1] = 1;
  (polyp + 3)->points[2] = 5;

  (polyp + 4)->points[0] = 4;
  (polyp + 4)->points[1] = 6;
  (polyp + 4)->points[2] = 3;

  (polyp + 5)->points[0] = 7;
  (polyp + 5)->points[1] = 8;
  (polyp + 5)->points[2] = 9;

  (polyp + 6)->points[0] = 5;
  (polyp + 6)->points[1] = 1;
  (polyp + 6)->points[2] = 10;

  (polyp + 7)->points[0] = 10;
  (polyp + 7)->points[1] = 1;
  (polyp + 7)->points[2] = 0;

  (polyp + 8)->points[0] = 10;
  (polyp + 8)->points[1] = 0;
  (polyp + 8)->points[2] = 8;

  (polyp + 9)->points[0] = 8;
  (polyp + 9)->points[1] = 0;
  (polyp + 9)->points[2] = 9;

  (polyp + 10)->points[0] = 5;
  (polyp + 10)->points[1] = 10;
  (polyp + 10)->points[2] = 4;

  (polyp + 11)->points[0] = 10;
  (polyp + 11)->points[1] = 8;
  (polyp + 11)->points[2] = 4;

  (polyp + 12)->points[0] = 4;
  (polyp + 12)->points[1] = 8;
  (polyp + 12)->points[2] = 7;

  (polyp + 13)->points[0] = 4;
  (polyp + 13)->points[1] = 7;
  (polyp + 13)->points[2] = 6;

  (polyp + 14)->points[0] = 6;
  (polyp + 14)->points[1] = 7;
  (polyp + 14)->points[2] = 11;

  (polyp + 15)->points[0] = 0;
  (polyp + 15)->points[1] = 2;
  (polyp + 15)->points[2] = 9;

  (polyp + 16)->points[0] = 9;
  (polyp + 16)->points[1] = 2;
  (polyp + 16)->points[2] = 7;

  (polyp + 17)->points[0] = 7;
  (polyp + 17)->points[1] = 2;
  (polyp + 17)->points[2] = 3;

  (polyp + 18)->points[0] = 7;
  (polyp + 18)->points[1] = 3;
  (polyp + 18)->points[2] = 11;

  (polyp + 19)->points[0] = 11;
  (polyp + 19)->points[1] = 3;
  (polyp + 19)->points[2] = 6;
  max_min_vertex(&vertex_arr_answer, &maxs_a, &mins_a);
  rescaling_and_centering(&vertex_arr_answer, maxs_a, mins_a, 0.5);
  ck_assert_int_eq(obj_file_full(filename, &vertex_arr, &polygon_arr), SUCCESS);
  vertex *pp = vertex_arr.vert;
  polygon *poly = polygon_arr.polygon;
  ck_assert_int_eq(vertex_arr.p_amount, vertex_arr_answer.p_amount);
  ck_assert_int_eq(polygon_arr.amount_poly, polygon_arr_answer.amount_poly);
  ck_assert_int_eq(polygon_arr.amount_edges, polygon_arr_answer.amount_edges);
  for (int i = 0; i < vertex_arr_answer.p_amount; i++) {
    ck_assert_double_eq_tol((pp + i)->x, (pp_a + i)->x, 10E-6);
    ck_assert_double_eq_tol((pp + i)->y, (pp_a + i)->y, 10E-6);
    ck_assert_double_eq_tol((pp + i)->z, (pp_a + i)->z, 10E-6);
  }
  for (int i = 0; i < polygon_arr_answer.amount_poly; i++) {
    ck_assert_int_eq((poly + i)->points[0], (polyp + i)->points[0]);
    ck_assert_int_eq((poly + i)->points[1], (polyp + i)->points[1]);
    ck_assert_int_eq((poly + i)->points[2], (polyp + i)->points[2]);
  }
  axis_values values = {0, 0, 0};
  values.x_axis = 0.1;
  values.z_axis = 0.15;
  transformation(&vertex_arr, translation, &values);

  for (int i = 0; i < vertex_arr_answer.p_amount; i++) {
    ck_assert_double_eq_tol((pp + i)->x, (pp_a + i)->x + 0.1, 10E-6);
    ck_assert_double_eq_tol((pp + i)->y, (pp_a + i)->y, 10E-6);
    ck_assert_double_eq_tol((pp + i)->z, (pp_a + i)->z + 0.15, 10E-6);
  }

  values.x_axis = 1;
  values.y_axis = 2;
  values.z_axis = 0.5;
  transformation(&vertex_arr, scaling, &values);

  for (int i = 0; i < vertex_arr_answer.p_amount; i++) {
    ck_assert_double_eq_tol((pp + i)->x, (pp_a + i)->x + 0.1, 10E-6);
    ck_assert_double_eq_tol((pp + i)->y, (pp_a + i)->y * 2, 10E-6);
    ck_assert_double_eq_tol((pp + i)->z, ((pp_a + i)->z + 0.15) * 0.5, 10E-6);
  }

  free(vertex_arr.vert);
  for (int i = 0; i < polygon_arr.amount_poly; i++) {
    free((poly + i)->points);
  }
  free(polygon_arr.polygon);

  free(vertex_arr_answer.vert);
  for (int i = 0; i < polygon_arr_answer.amount_poly; i++) {
    free((polyp + i)->points);
  }
  free(polygon_arr_answer.polygon);
}
END_TEST

START_TEST(simple_test_2) {
  char *filename = "models/truncated-tetrahedron1.obj";
  vertexes vertex_arr = {0, 0};
  polygons polygon_arr = {0, 0, 0};
  ck_assert_int_eq(obj_file_parser(filename, &vertex_arr, &polygon_arr),
                   FAILURE);
}
END_TEST

START_TEST(simple_test_3) {
  char *filename = "models/cube.obj";
  vertexes vertex_arr = {0, 0};
  polygons polygon_arr = {0, 0, 0};
  vertexes vertex_arr_answer = {0, 0};
  polygons polygon_arr_answer = {0, 0, 0};
  vertex maxs_a = {0, 0, 0};
  vertex mins_a = {0, 0, 0};
  vertex_arr_answer.p_amount = 8;
  polygon_arr_answer.amount_poly = 12;
  polygon_arr_answer.amount_edges = 18;
  create_vertex_polygon(8, &vertex_arr_answer, 12, &polygon_arr_answer);
  vertex *pp_a = vertex_arr_answer.vert;
  polygon *polyp = polygon_arr_answer.polygon;

  (pp_a + 0)->x = -0.500000;
  (pp_a + 0)->y = -0.500000;
  (pp_a + 0)->z = 0.500000;

  (pp_a + 1)->x = 0.500000;
  (pp_a + 1)->y = -0.500000;
  (pp_a + 1)->z = 0.500000;

  (pp_a + 2)->x = -0.500000;
  (pp_a + 2)->y = 0.500000;
  (pp_a + 2)->z = 0.500000;

  (pp_a + 3)->x = 0.500000;
  (pp_a + 3)->y = 0.500000;
  (pp_a + 3)->z = 0.500000;

  (pp_a + 4)->x = -0.500000;
  (pp_a + 4)->y = 0.500000;
  (pp_a + 4)->z = -0.500000;

  (pp_a + 5)->x = 0.500000;
  (pp_a + 5)->y = 0.500000;
  (pp_a + 5)->z = -0.500000;

  (pp_a + 6)->x = -0.500000;
  (pp_a + 6)->y = -0.500000;
  (pp_a + 6)->z = -0.500000;

  (pp_a + 7)->x = 0.500000;
  (pp_a + 7)->y = -0.500000;
  (pp_a + 7)->z = -0.500000;

  for (size_t i = 0; i < 12; i++) {
    (polyp + i)->points = calloc(3, sizeof(int));
    (polyp + i)->amount_points = 3;
  }
  (polyp + 0)->points[0] = 0;
  (polyp + 0)->points[1] = 1;
  (polyp + 0)->points[2] = 2;

  (polyp + 1)->points[0] = 2;
  (polyp + 1)->points[1] = 1;
  (polyp + 1)->points[2] = 3;

  (polyp + 2)->points[0] = 2;
  (polyp + 2)->points[1] = 3;
  (polyp + 2)->points[2] = 4;

  (polyp + 3)->points[0] = 4;
  (polyp + 3)->points[1] = 3;
  (polyp + 3)->points[2] = 5;

  (polyp + 4)->points[0] = 4;
  (polyp + 4)->points[1] = 5;
  (polyp + 4)->points[2] = 6;

  (polyp + 5)->points[0] = 6;
  (polyp + 5)->points[1] = 5;
  (polyp + 5)->points[2] = 7;

  (polyp + 6)->points[0] = 6;
  (polyp + 6)->points[1] = 7;
  (polyp + 6)->points[2] = 0;

  (polyp + 7)->points[0] = 0;
  (polyp + 7)->points[1] = 7;
  (polyp + 7)->points[2] = 1;

  (polyp + 8)->points[0] = 1;
  (polyp + 8)->points[1] = 7;
  (polyp + 8)->points[2] = 3;

  (polyp + 9)->points[0] = 3;
  (polyp + 9)->points[1] = 7;
  (polyp + 9)->points[2] = 5;

  (polyp + 10)->points[0] = 6;
  (polyp + 10)->points[1] = 0;
  (polyp + 10)->points[2] = 4;

  (polyp + 11)->points[0] = 4;
  (polyp + 11)->points[1] = 0;
  (polyp + 11)->points[2] = 2;

  max_min_vertex(&vertex_arr_answer, &maxs_a, &mins_a);
  rescaling_and_centering(&vertex_arr_answer, maxs_a, mins_a, 0.5);

  ck_assert_int_eq(obj_file_full(filename, &vertex_arr, &polygon_arr), SUCCESS);
  vertex *pp = vertex_arr.vert;
  polygon *poly = polygon_arr.polygon;
  ck_assert_int_eq(vertex_arr.p_amount, vertex_arr_answer.p_amount);
  ck_assert_int_eq(polygon_arr.amount_poly, polygon_arr_answer.amount_poly);
  ck_assert_int_eq(polygon_arr.amount_edges, polygon_arr_answer.amount_edges);
  for (int i = 0; i < vertex_arr_answer.p_amount; i++) {
    ck_assert_double_eq_tol((pp + i)->x, (pp_a + i)->x, 10E-6);
    ck_assert_double_eq_tol((pp + i)->y, (pp_a + i)->y, 10E-6);
    ck_assert_double_eq_tol((pp + i)->z, (pp_a + i)->z, 10E-6);
  }
  for (int i = 0; i < polygon_arr_answer.amount_poly; i++) {
    ck_assert_int_eq((poly + i)->points[0], (polyp + i)->points[0]);
    ck_assert_int_eq((poly + i)->points[1], (polyp + i)->points[1]);
    ck_assert_int_eq((poly + i)->points[2], (polyp + i)->points[2]);
  }

  axis_values values = {0, 0, 0};
  values.x_axis = 30;
  // values->y_axis = 45;
  // values->z_axis = 90;

  (pp_a + 0)->x = -0.500000;
  (pp_a + 0)->y = -0.6830125;
  (pp_a + 0)->z = 0.1830125;

  (pp_a + 1)->x = 0.500000;
  (pp_a + 1)->y = -0.6830125;
  (pp_a + 1)->z = 0.1830125;

  (pp_a + 2)->x = -0.500000;
  (pp_a + 2)->y = 0.1830125;
  (pp_a + 2)->z = 0.6830125;

  (pp_a + 3)->x = 0.500000;
  (pp_a + 3)->y = 0.1830125;
  (pp_a + 3)->z = 0.6830125;

  (pp_a + 4)->x = -0.500000;
  (pp_a + 4)->y = 0.6830125;
  (pp_a + 4)->z = -0.1830125;

  (pp_a + 5)->x = 0.500000;
  (pp_a + 5)->y = 0.6830125;
  (pp_a + 5)->z = -0.1830125;

  (pp_a + 6)->x = -0.500000;
  (pp_a + 6)->y = -0.1830125;
  (pp_a + 6)->z = -0.6830125;

  (pp_a + 7)->x = 0.500000;
  (pp_a + 7)->y = -0.1830125;
  (pp_a + 7)->z = -0.6830125;
  transformation(&vertex_arr, rotation, &values);

  for (int i = 0; i < vertex_arr_answer.p_amount; i++) {
    ck_assert_double_eq_tol((pp + i)->x, (pp_a + i)->x, 10E-5);
    ck_assert_double_eq_tol((pp + i)->y, (pp_a + i)->y, 10E-5);
    ck_assert_double_eq_tol((pp + i)->z, (pp_a + i)->z, 10E-5);
  }

  values.x_axis = 0;
  values.y_axis = 45;
  // values->z_axis = 90;

  (pp_a + 0)->x = -0.224145;
  (pp_a + 0)->y = -0.6830125;
  (pp_a + 0)->z = 0.482965;

  (pp_a + 1)->x = 0.482965;
  (pp_a + 1)->y = -0.6830125;
  (pp_a + 1)->z = -0.224145;

  (pp_a + 2)->x = 0.12941;
  (pp_a + 2)->y = 0.1830125;
  (pp_a + 2)->z = 0.83652;

  (pp_a + 3)->x = 0.83652;
  (pp_a + 3)->y = 0.1830125;
  (pp_a + 3)->z = 0.12941;

  (pp_a + 4)->x = -0.482965;
  (pp_a + 4)->y = 0.6830125;
  (pp_a + 4)->z = 0.224145;

  (pp_a + 5)->x = 0.224145;
  (pp_a + 5)->y = 0.6830125;
  (pp_a + 5)->z = -0.482965;

  (pp_a + 6)->x = -0.83652;
  (pp_a + 6)->y = -0.1830125;
  (pp_a + 6)->z = -0.12941;

  (pp_a + 7)->x = -0.12941;
  (pp_a + 7)->y = -0.1830125;
  (pp_a + 7)->z = -0.83652;

  transformation(&vertex_arr, rotation, &values);
  for (int i = 0; i < vertex_arr_answer.p_amount; i++) {
    ck_assert_double_eq_tol((pp + i)->x, (pp_a + i)->x, 10E-5);
    ck_assert_double_eq_tol((pp + i)->y, (pp_a + i)->y, 10E-5);
    ck_assert_double_eq_tol((pp + i)->z, (pp_a + i)->z, 10E-5);
  }

  values.x_axis = 0;
  values.y_axis = 0;
  values.z_axis = 90;

  (pp_a + 0)->x = 0.6830125;
  (pp_a + 0)->y = -0.224145;
  (pp_a + 0)->z = 0.482965;

  (pp_a + 1)->x = 0.6830125;
  (pp_a + 1)->y = 0.482965;
  (pp_a + 1)->z = -0.224145;

  (pp_a + 2)->x = -0.1830125;
  (pp_a + 2)->y = 0.12941;
  (pp_a + 2)->z = 0.83652;

  (pp_a + 3)->x = -0.1830125;
  (pp_a + 3)->y = 0.83652;
  (pp_a + 3)->z = 0.12941;

  (pp_a + 4)->x = -0.6830125;
  (pp_a + 4)->y = -0.482965;
  (pp_a + 4)->z = 0.224145;

  (pp_a + 5)->x = -0.6830125;
  (pp_a + 5)->y = 0.224145;
  (pp_a + 5)->z = -0.482965;

  (pp_a + 6)->x = 0.1830125;
  (pp_a + 6)->y = -0.83652;
  (pp_a + 6)->z = -0.12941;

  (pp_a + 7)->x = 0.1830125;
  (pp_a + 7)->y = -0.12941;
  (pp_a + 7)->z = -0.83652;

  transformation(&vertex_arr, rotation, &values);
  for (int i = 0; i < vertex_arr_answer.p_amount; i++) {
    ck_assert_double_eq_tol((pp + i)->x, (pp_a + i)->x, 10E-5);
    ck_assert_double_eq_tol((pp + i)->y, (pp_a + i)->y, 10E-5);
    ck_assert_double_eq_tol((pp + i)->z, (pp_a + i)->z, 10E-5);
  }

  free(vertex_arr.vert);
  for (int i = 0; i < polygon_arr.amount_poly; i++) {
    free((poly + i)->points);
  }
  free(polygon_arr.polygon);

  free(vertex_arr_answer.vert);
  for (int i = 0; i < polygon_arr_answer.amount_poly; i++) {
    free((polyp + i)->points);
  }
  free(polygon_arr_answer.polygon);
}
END_TEST

START_TEST(simple_test_4) {
  char *filename = "models/null.obj";
  vertexes vertex_arr = {0, 0};
  polygons polygon_arr = {0, 0, 0};
  ck_assert_int_eq(obj_file_full(filename, &vertex_arr, &polygon_arr), FAILURE);
}
END_TEST

START_TEST(simple_test_5) {
  char *filename = "models/aboba.obj";
  vertexes vertex_arr = {0, 0};
  polygons polygon_arr = {0, 0, 0};
  ck_assert_int_eq(obj_file_full(filename, &vertex_arr, &polygon_arr), FAILURE);
}
END_TEST

Suite *cube(void) {
  Suite *s = suite_create("\033[46m-=cube=-\033[0m");
  TCase *tc = tcase_create("calc_rc");

  tcase_add_test(tc, simple_test_3);

  suite_add_tcase(s, tc);
  return s;
}

Suite *tetraedr(void) {
  Suite *s = suite_create("\033[44m-=trunc-tetraedr=-\033[0m");
  TCase *tc = tcase_create("calc_rc");

  tcase_add_test(tc, simple_test_1);

  suite_add_tcase(s, tc);
  return s;
}

Suite *exeptions(void) {
  Suite *s = suite_create("\033[46m-=exeptions=-\033[0m");
  TCase *tc = tcase_create("calc_rc");

  tcase_add_test(tc, simple_test_2);
  tcase_add_test(tc, simple_test_4);
  tcase_add_test(tc, simple_test_5);

  suite_add_tcase(s, tc);
  return s;
}

int main(void) {
  int failed = 0;
  Suite *viewer_t_test[] = {cube(), tetraedr(), exeptions(), NULL};

  for (int i = 0; viewer_t_test[i] != NULL; i++) {
    SRunner *sr = srunner_create(viewer_t_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }

  if (failed == 0) {
    printf("\033[1;42m -=SUCCESS=- \033[0m\n");
  } else {
    printf("\033[1;41m -=FAILED=- \033[0m\n");
  }

  return failed == 0 ? 0 : 1;
}
