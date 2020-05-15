#include "phase1.h"

static void clean_string(char* path) {  // function used purely to remove the \n in the text paths.
	//  Assume \n only occurs at end
	for(int i = 0; path[i] != '\0'; i++) {
		if(path[i] == '\n') {
			path[i] = '\0';
			break;
		}
	}
}

// trim empty space
static void trim(char * s) {
    char * p = s;
    int l = strlen(p);

    while(isspace(p[l - 1])) p[--l] = 0;
    while(* p && isspace(* p)) ++p, --l;

    memmove(s, p, l + 1);
}
//  make sure arg for width/height is composed completely of digits
static int arg_digit(char *word) {

  for(int i = 0; i < strlen(word); i++) {
		//  checks for a-z , A-Z
		//  e check in case of float
    if(isalpha(word[i]) && word[i] != 'e') {

      return 0;
    }
  }
  return 1;
}
//  process input file
int process_file(char *fname) {
	FILE* fp = fopen(fname, "r");
	//char line[LINE_SIZE];

	if (!fp) {
		printf("Failed to open the file: %s \n", fname);
		return -1;
	}

	//  Read the contents and store in line*s
  //  just need to read in one line
	int i = 0;
	while(fgets(file_line[i], LINE_SIZE, fp)) {
		//  check if goes over file line buffer
		if (i+1 > R_SIZE) {
			printf("OVER FILE LINE BUFFER");
			return -1;
		}
		//  null terminate string
		file_line[i][strlen(file_line[i])-1] = '\0';
		i++;
	}
	fclose(fp);

	line_count = i;

	return 0;
}

///////////////////////////////////////////////////////////////////////
//  function to process the texture input file
int process_texture(char *fname) {
	char *line_buf = NULL;
	size_t line_buf_size = 0;
	int line_count = 0;
	ssize_t line_size;
  FILE* fp = fopen(fname, "r");
	if (!fp) {
		printf("Failed to open the file: %s \n", fname);
		return -1;
	}

	//  get first line of the file
	line_size = getline(&line_buf, &line_buf_size, fp);
	int max_color;

	//  parse first line and malloc arrays
	if (line_count == 0 && sscanf(line_buf, "P3 %d %d %d", &t_width, &t_height, &max_color) == 3) {
		text_index++;
		//  dynamically size array for u and v
		m_array[text_index] = (ColorType **)malloc(t_height * sizeof(ColorType *));

		for (int i = 0 ; i < t_height ; i++) {
			m_array[text_index][i] = (ColorType *)malloc((t_width) * sizeof (ColorType));
		}

		//  increment line count
		line_count++;

	} else {
		//  invalid first line format
		printf("invalid first line format\n");
		return -1;
	}

	//  input r,g,b colors into m_array
	//  line_count at 1
	line_count = 0;

	for (int v = 0 ; v < t_height; v++) {
		for (int u = 0; u < t_width; u++) {
			// color texture
			////////////////
			int a,b,c;
			line_size = getline(&line_buf, &line_buf_size, fp);
			//  test to see if color exists
			if (line_size <= 0) {
				printf("missing color\n");
				return -1;
			}

			if (sscanf(line_buf, "%d %d %d", &a, &b, &c) == 3) {
				float temp1 = (float) a/max_color;
				float temp2 = (float) b/max_color;
				float temp3 = (float) c/max_color;

				m_array[text_index][v][u].r = temp1;
				m_array[text_index][v][u].g = temp2;
				m_array[text_index][v][u].b = temp3;
				line_count = line_count + 3;
			//  reads r g b on multiple lines
			} else if (sscanf(line_buf, "%d", &a) == 1) {
				//  red
				float temp1 = (float) a/max_color;
				m_array[text_index][v][u].r = temp1;
				line_count++;

				//  green
				line_size = getline(&line_buf, &line_buf_size, fp);
				sscanf(line_buf, "%d", &a);
				float temp2 = (float) a/max_color;
				m_array[text_index][v][u].g = temp2;
				line_count++;

				//  blue
				line_size = getline(&line_buf, &line_buf_size, fp);
				sscanf(line_buf, "%d", &a);
				float temp3 = (float) a/max_color;
				m_array[text_index][v][u].b = temp3;
				line_count++;
			} else {
				//invalid format
				printf("invalid format use formatted valid ppm\n");
				return -1;
			}
		}
	}

	return 0;
}

//  parse the text file into tokens
int parser(char * test_line) {
	clean_string(test_line);
	//  check if line is empty then return
	if (test_line[0] == '\0') {
		return 0;
	}

	char p_line[R_SIZE];
	char t_line[R_SIZE];
	// use to test triangles
	strcpy(t_line, test_line);
	// use to str tok
	strcpy(p_line, test_line);

  char* token = strtok(p_line, " ");
  static char* store[MAX_VARS];

  int i = 0;

  while (token != NULL) {
    //  store keyword and vars into store
    store[i++] = token;

    token = strtok(NULL, " ");
  }
	//  cases for all variables
	//  need to make sure all are satisfied
	//  need to make sure that iterate for all vars
	/////////////////////////////
	//  get count of how many variables were stored
	int count = i;

  if (strcmp(store[0], "imsize") == 0) {
		//  prase for imsize
		//  check if number of arguments supplied is enough
		if (count != 3) {
			printf("incorrect arguments for imsize\n");
			return -1;
		}

		//  check if string is composed of digits or not
		if (arg_digit(store[1]) == 0 || arg_digit(store[2]) == 0) {
			printf("incorrect input for imsize\n");
			return -1;
		}
		clean_string(store[1]);
		clean_string(store[2]);

		width = atoi(store[1]);
		height = atoi(store[2]);
		if (width < 0 || height < 0) {
			printf("invalid input for imsize\n");
			return -1;
		}
		arg_1 = true;
		return 0;

	} else if (strcmp(store[0], "eye") == 0) {
		//  parse for eye
		//  check if number of arguments supplied is enough
		if (count != 4) {
			printf("incorrect number of arguments provided for eye\n");
			return -1;
		}

		//  check if inputs are valid
		//  floats
		if (arg_digit(store[1]) == 0 || arg_digit(store[2]) == 0
		|| arg_digit(store[3]) == 0) {
			printf("incorrect input for eye\n");
			return -1;
		}

		//  store values into eye
		eye.x = atof(store[1]);
		eye.y = atof(store[2]);
		eye.z = atof(store[3]);

		arg_2 = true;
		return 0;

	} else if (strcmp(store[0], "viewdir") == 0) {
		//  parse for viewdir
		//  check if number of arguments supplied is enough
		if (count != 4) {
			printf("incorrect number of arguments provided to viewdir\n");
			return -1;
		}
		//  check if inputs are valid
		//  floats
		if (arg_digit(store[1]) == 0 || arg_digit(store[2]) == 0
		|| arg_digit(store[3]) == 0) {
			printf("incorrect input for viewdir\n");
			return -1;
		}

		//  store values into viewdir
		viewdir.x = atof(store[1]);
		viewdir.y = atof(store[2]);
		viewdir.z = atof(store[3]);

		if (viewdir.x == 0 && viewdir.y == 0 && viewdir.z == 0) {
			printf("viewdir vector 0\n");
			return -1;
		}
		arg_3 = true;
		return 0;

	} else if (strcmp(store[0], "updir") == 0) {
		//  parse for updir
		//  check if number of arguments supplied is enough
		if (count != 4) {
			printf("incorrect number of arguments provided to updir\n");
			return -1;
		}
		//  check if inputs are valid
		//  floats
		if (arg_digit(store[1]) == 0 || arg_digit(store[2]) == 0
		|| arg_digit(store[3]) == 0) {
			printf("incorrect input for updir");
			return -1;
		}

		//  store values into viewdir
		updir.x = atof(store[1]);
		updir.y = atof(store[2]);
		updir.z = atof(store[3]);

		if (updir.x == 0 && updir.y == 0 && updir.z == 0) {
			printf("updir vector 0\n");
			return -1;
		}

		arg_4 = true;
		return 0;

	//TODO GETTING ERROR WITH BUFFER 178>= degrees
	} else if (strcmp(store[0], "hfov") == 0) {
		//  parse for hfov
		//  check if number of arguments supplied is enough
		if (count != 2) {
			printf("incorrect number of arguments provided for hfov\n");
			return -1;
		}

		//  check if inputs are valid
		//  floats
		if (arg_digit(store[1]) == 0){
			printf("incorrect input for hfov\n");
			return -1;
		}

		//  store values into hfov
		hfov = atof(store[1]);

		//  check if hfov is greater than or equal to 180 or less than 0
		//  177 to prevent errors refer to todo above
		if (hfov >= 177 || hfov < 0) {
			printf("hfov error");
			return -1;
		}

		arg_5 = true;
		return 0;

	} else if (strcmp(store[0], "bkgcolor") == 0) {
		//  parse for bkgcolor
		//  check if number of arguments supplied is enough
		if (count != 4) {
			printf("incorrect number of arguments provided for bkgcolor\n");
			return -1;
		}

		//  check if inputs are valid
		//  floats
		if (arg_digit(store[1]) == 0 || arg_digit(store[2]) == 0
		|| arg_digit(store[3]) == 0) {
			printf("incorrect input for bkgcolor\n");
			return -1;
		}

		//  store values into viewdir

		bkgcolor.r = atof(store[1]);
		bkgcolor.g = atof(store[2]);
		bkgcolor.b = atof(store[3]);

		//  if over 1 or below 0 input
		if (bkgcolor.r > 1 || bkgcolor.r < 0) {
			printf("incorrect format  for bkgcolor\n");
			return -1;
		}
		if (bkgcolor.g > 1 || bkgcolor.g < 0) {
			printf("incorrect format  for bkgcolor\n");
			return -1;
		}
		if (bkgcolor.b > 1 || bkgcolor.b < 0) {
			printf("incorrect format  for bkgcolor\n");
			return -1;
		}
		arg_6 = true;
		return 0;

	} else if (strcmp(store[0], "light") == 0) {

		//  parse for light
		//  check if number of arguments supplied is enough
		if (count != 8) {
			printf("incorrect number of arguments provided for light\n");
			return -1;
		}

		//  check if inputs are valid
		//  floats
		if (arg_digit(store[1]) == 0 || arg_digit(store[2]) == 0
		|| arg_digit(store[3]) == 0 || arg_digit(store[4]) == 0
		|| arg_digit(store[5]) == 0 || arg_digit(store[6]) == 0
		|| arg_digit(store[7]) == 0) {
			printf("incorrect input for light\n");
			return -1;
		}

		l_index++;
		//  can only store max 100 light sources
		if (l_index > 99) {
			printf("light sources surpassed (100)\n");
			return -1;
		}

		// store light variables
		light[l_index].x = atof(store[1]);
		light[l_index].y = atof(store[2]);
		light[l_index].z = atof(store[3]);
		light[l_index].w = atoi(store[4]);
		light[l_index].r = atof(store[5]);
		light[l_index].g = atof(store[6]);
		light[l_index].b = atof(store[7]);

		//  if over 1 or below 0 input
		if (light[l_index].r > 1.0 || light[l_index].r < 0.0) {
			printf("incorrect format  for light r\n");
			return -1;
		}
		if (light[l_index].g > 1.0 || light[l_index].g < 0.0) {
			printf("incorrect format  for light g\n");
			return -1;
		}
		if (light[l_index].b > 1.0 || light[l_index].b < 0.0) {
			printf("incorrect format  for light b\n");
			return -1;
		}
		//  check if light w format is off
		if (!(light[l_index].w == 0 || light[l_index].w == 1)) {
			printf("incorrect format  for light w\n");
			return -1;
		}
		arg_7 = true;
		return 0;

	} else if (strcmp(store[0], "mtlcolor") == 0) {

		//  parse for mtlcolor
		//  check if number of arguments supplied is enough
		if (count != 13) {
			printf("incorrect number of arguments provided to mtlcolor\n");
			return -1;
		}

		//  check if inputs are valid
		//  floats
		if (arg_digit(store[1]) == 0 || arg_digit(store[2]) == 0
		|| arg_digit(store[3]) == 0 || arg_digit(store[4]) == 0 || arg_digit(store[5]) == 0
		|| arg_digit(store[6]) == 0 || arg_digit(store[7]) == 0 || arg_digit(store[8]) == 0
		|| arg_digit(store[9]) == 0 || arg_digit(store[10]) == 0|| arg_digit(store[11]) == 0
	|| arg_digit(store[12]) == 0) {
			printf("incorrect input for mtlcolor\n");
			return -1;
		}

		//  store values into viewdir
		//  index into respective mtlcolor
		m_index++;
		//  can only store max 100 material colors
		if (m_index > 99) {
			printf("max material colors surpassed (100)\n");
			return -1;
		}
		mtlcolor[m_index].r = atof(store[1]);
		mtlcolor[m_index].g = atof(store[2]);
		mtlcolor[m_index].b = atof(store[3]);
		mtlcolor[m_index].sr = atof(store[4]);
		mtlcolor[m_index].sg = atof(store[5]);
		mtlcolor[m_index].sb = atof(store[6]);
		mtlcolor[m_index].ka = atof(store[7]);
		mtlcolor[m_index].kd = atof(store[8]);
		mtlcolor[m_index].ks = atof(store[9]);
		mtlcolor[m_index].n = atoi(store[10]);
		mtlcolor[m_index].o = atof(store[11]);
		mtlcolor[m_index].ref = atof(store[12]);
		//printf("opacity: %f\n" ,mtlcolor[m_index].o);
		//printf("ref ind: %f\n" ,mtlcolor[m_index].ref);
		//printf("ref ind s: %s\n" ,store[12]);
		//  if over 1 or below 0 input
		if (mtlcolor[m_index].r > 1.0 || mtlcolor[m_index].r < 0.0) {
			printf("incorrect format  for mtlcolor\n");
			return -1;
		}
		if (mtlcolor[m_index].g > 1.0 || mtlcolor[m_index].g < 0.0) {
			printf("incorrect format  for mtlcolor\n");
			return -1;
		}
		if (mtlcolor[m_index].b > 1.0 || mtlcolor[m_index].b < 0.0) {
			printf("incorrect format  for mtlcolor\n");
			return -1;
		}
		if (mtlcolor[m_index].sr > 1.0 || mtlcolor[m_index].sr < 0.0) {
			printf("incorrect format  for mtlcolor\n");
			return -1;
		}
		if (mtlcolor[m_index].sg > 1.0 || mtlcolor[m_index].sg < 0.0) {
			printf("incorrect format  for mtlcolor\n");
			return -1;
		}
		if (mtlcolor[m_index].sb > 1.0 || mtlcolor[m_index].sb < 0.0) {
			printf("incorrect format  for mtlcolor\n");
			return -1;
		}
		if (mtlcolor[m_index].o > 1.0 || mtlcolor[m_index].o < 0.0) {
			printf("incorrect format  for mtlcolor\n");
			return -1;
		}
		if (mtlcolor[m_index].ref < 0.0) {
			printf("incorrect format  for mtlcolor\n");
			return -1;
		}
		//  spheres can now be generated
		check = true;

		return 0;

	} else if (strcmp(store[0], "sphere") == 0) {

		//  parse for sphere
		//  check if mtlcolor specified
		if (check == false) {
			printf("mtlcolor not specified for sphere\n");
			return -1;
		}

		//  check if number of arguments supplied is enough
		if (count != 5) {
			printf("incorrect number of arguments provided to sphere\n");
			return -1;
		}

		//  check if inputs are valid
		//  floats
		if (arg_digit(store[1]) == 0 || arg_digit(store[2]) == 0
		|| arg_digit(store[3]) == 0 || arg_digit(store[4]) == 0) {
			printf("incorrect inputs for sphere\n");
			return -1;
		}

		//  store values into viewdir

		s_index++;
		//  can only store max of 5000 spheres
		if (s_index > 4999) {
			printf("max sphere surpassed (5000)\n");
			return -1;
		}

		sphere[s_index].x = atof(store[1]);
		sphere[s_index].y = atof(store[2]);
		sphere[s_index].z = atof(store[3]);
		sphere[s_index].r = atof(store[4]);
		sphere[s_index].m = m_index;
		sphere[s_index].text = check2;
		sphere[s_index].texture = text_index;

		//  check if radius for sphere is negative
		if (sphere[s_index].r < 0) {
			printf("negative radius for sphere\n");
			return -1;
		}
		return 0;
///////////  vertex
	} else if (strcmp(store[0], "v") == 0) {

		//  check if number of arguments supplied is enough
		if (count != 4) {
			printf("incorrect number of arguments provided to vertex\n");
			return -1;
		}

		//  check if inputs are valid
		//  floats
		if (arg_digit(store[1]) == 0 || arg_digit(store[2]) == 0
		|| arg_digit(store[3]) == 0) {
			printf("%s %s %s\n", store[1], store[2], store[3]);
			printf("incorrect inputs for vertex\n");
			return -1;
		}

		v_index++;
		//  can only store max of 5000 vertices
		if (v_index > 5000) {
			printf("max vertex surpassed (5000)\n");
			return -1;
		}

		//  v_index starts at 1 , skips 0
		vertex[v_index].x = atof(store[1]);
		vertex[v_index].y = atof(store[2]);
		vertex[v_index].z = atof(store[3]);

		return 0;
	///////////////// triangle different types
	// DIFFERENT TYPES OF FORMAT
	} else if (strcmp(store[0], "vn") == 0) {

		//  check if number of arguments supplied is enough
		if (count != 4) {
			printf("incorrect number of arguments provided to vn\n");
			return -1;
		}

		//  check if inputs are valid
		//  floats
		if (arg_digit(store[1]) == 0 || arg_digit(store[2]) == 0
		|| arg_digit(store[3]) == 0) {
			printf("incorrect inputs for vn\n");
			return -1;
		}

		//  store values into viewdir

		n_index++;
		//  can only store max of 5000 normal
		if (n_index > 5000) {
			printf("max normal surpassed (5000)\n");
			return -1;
		}

		//  normal starts at 1
		normal[n_index].x = atof(store[1]);
		normal[n_index].y = atof(store[2]);
		normal[n_index].z = atof(store[3]);

		return 0;
	///////////////// triangle different types
	// DIFFERENT TYPES OF FORMAT
	} else if (strcmp(store[0], "f") == 0) {

		// remove first char f
		char *t_new = t_line+1;
		trim(t_new);
		int a, b, c, d, e, f, g, h, i;

		//  smooth and shaded
		if (sscanf(t_new, "%d/%d/%d %d/%d/%d %d/%d/%d", &a, &b, &c, &d, &e, &f, &g, &h, &i) == 9) {
			//  increment triangle count
			t_index++;
			//  can only store max of 300 triangles
			if (t_index > 5000) {
				printf("max st triangle surpassed 5000)\n");
				return -1;
			}

			//  stores integers greater than 0
			triangle[t_index].v1 = a;
			triangle[t_index].v2 = d;
			triangle[t_index].v3 = g;
			triangle[t_index].vn1 = c;
			triangle[t_index].vn2 = f;
			triangle[t_index].vn3 = i;
			triangle[t_index].vt1 = b;
			triangle[t_index].vt2 = e;
			triangle[t_index].vt3 = g;
			triangle[t_index].m = m_index;
			triangle[t_index].t = 3;
			triangle[t_index].text = check2;
			triangle[t_index].texture = text_index;
			//  check if vertices index is 0 or negative
			if (triangle[t_index].v1 <= 0 || triangle[t_index].v2 <= 0 || triangle[t_index].v3 <= 0) {
				printf("triangle tst vertex invalid\n");
				return -1;
			}
			//  check if vertices index is 0 or negative
			if (triangle[t_index].vn1 <= 0 || triangle[t_index].vn2 <= 0 || triangle[t_index].vn3 <= 0) {
				printf("triangle tst vertex invalid\n");
				return -1;
			}
			//  check if vertices index is 0 or negative
			if (triangle[t_index].vt1 <= 0 || triangle[t_index].vt2 <= 0 || triangle[t_index].vt3 <= 0) {
				printf("triangle tst vertex invalid\n");
				return -1;
			}

			return 0;
			//  smooth / untextured
		} else if (sscanf(t_new, "%d//%d %d//%d %d//%d", &a, &b, &c, &d, &e, &f) == 6) {
			//  increment triangle count
			t_index++;
			//  can only store max of 5000 triangles
			if (t_index > 5000) {
				printf("max ts triangle surpassed 5000)\n");
				return -1;
			}

			//  stores integers greater than 0
			triangle[t_index].v1 = a;
			triangle[t_index].v2 = c;
			triangle[t_index].v3 = e;
			triangle[t_index].vn1 = b;
			triangle[t_index].vn2 = d;
			triangle[t_index].vn3 = f;
			triangle[t_index].m = m_index;
			triangle[t_index].t = 1;
			triangle[t_index].text = false;
			triangle[t_index].texture = text_index;
			//  check if vertices index is 0 or negative
			if (triangle[t_index].v1 <= 0 || triangle[t_index].v2 <= 0 || triangle[t_index].v3 <= 0) {
				printf("triangle ts vertex invalid\n");
				return -1;
			}
			//  check if vertices index is 0 or negative
			if (triangle[t_index].vn1 <= 0 || triangle[t_index].vn2 <= 0 || triangle[t_index].vn3 <= 0) {
				printf("triangle ts vertex invalid\n");
				return -1;
			}

			return 0;

			//  textured/ no smoothshading
		} else if (sscanf(t_new, "%d/%d %d/%d %d/%d", &a, &b, &c, &d, &e, &f) == 6) {
			//  increment triangle count
			t_index++;
			//  can only store max of 300 triangles
			if (t_index > 5000) {
				printf("max tt triangle surpassed 5000)\n");
				return -1;
			}

			//  stores integers greater than 0
			triangle[t_index].v1 = a;
			triangle[t_index].v2 = c;
			triangle[t_index].v3 = e;
			triangle[t_index].vt1 = b;
			triangle[t_index].vt2 = d;
			triangle[t_index].vt3 = f;
			triangle[t_index].m = m_index;
			triangle[t_index].t = 2;
			triangle[t_index].text = check2;
			triangle[t_index].texture = text_index;
			//  check if vertices index is 0 or negative
			/*
			if (triangle[t_index].v1 <= 0 || triangle[t_index].v2 <= 0 || triangle[t_index].v3 <= 0) {
				printf("triangle tt vertex invalid\n");
				return -1;
			}
			//  check if vertices index is 0 or negative
			if (triangle[t_index].vt1 <= 0 || triangle[t_index].vt2 <= 0 || triangle[t_index].vt3 <= 0) {
				printf("triangle tt vertex invalid\n");
				return -1;
			}
			*/
			return 0;
			//  base triangle
		} else if (sscanf(t_new, "%d %d %d", &a, &b, &c) == 3) {

			//  increment triangle count
			t_index++;
			//  can only store max of 5000 triangles
			if (t_index > 5000) {
				printf("max triangle surpassed 5000)\n");
				return -1;
			}

			//  stores integers greater than 0
			triangle[t_index].v1 = a;
			triangle[t_index].v2 = b;
			triangle[t_index].v3 = c;
			triangle[t_index].m = m_index;
			triangle[t_index].t = 0;
			triangle[t_index].text = check2;
			triangle[t_index].texture = text_index;
			//  check if vertices index is 0 or negative
			if (triangle[t_index].v1 <= 0 || triangle[t_index].v2 <= 0 || triangle[t_index].v3 <= 0) {
				printf("triangle vertex value is 0\n");
				return -1;
			}

			return 0;


		} else {
			printf("error in triangle format");
			return -1;

		}
	} else if (strcmp(store[0], "texture") == 0) {
		//  parse for eye
		//  check if number of arguments supplied is enough
		if (count != 2) {
			printf("incorrect number of arguments provided for eye\n");
			return -1;
		}

		char file_name[LINE_SIZE];
		//  store file name
		if (sscanf(store[1], "%s", file_name) == 1) {
			check2 = true;
			return process_texture(file_name);

		} else {
			//  wrong number of argument
			printf("process_texture failed");
			return -1;
		}

	} else if (strcmp(store[0], "vt")==0) {

		//  increment triangle count
		vt_index++;
		//  can only store max of 5000 triangles
		if (vt_index > 5000) {
			printf("max vertex surpassed 5000)\n");
			return -1;
		}

		//  stores integers greater than 0
		vertext[vt_index].i = atof(store[1]);
		vertext[vt_index].j = atof(store[2]);

		return 0;

	} else {

		printf("%s \n", store[0]);
		if (store[0][0] == '#') {
			return 0;
		}
		//  error in format
		printf("error format no matching\n");

		return -1;

	}
	printf("ERROR Out of statement\n");
	return -1;
}

//  initialize all the variables with parser
int init_vars() {
	m_index = -1;
	s_index = -1;
	l_index = -1;
	//  v starts at 1 and t starts at 1
	//  index of normal
	n_index = 0;
	//  index of vertices
	v_index = 0;
	//  index of vertices
	vt_index = 0;
	//  index of base triangle
	t_index = 0;
	//  check that mtl color precedes sphere
	check = false;
	//  check that texture exists
	check2 = false;
	//  check that required arguments are provided (ex: eye, etc)
	arg_1 = false;
	arg_2 = false;
	arg_3 = false;
	arg_4 = false;
	arg_5 = false;
	arg_6 = false;
	arg_7 = false;

	m_array = (ColorType ***)malloc(MAX_TEXTURE*sizeof(ColorType **));
	text_index = -1;
	int j = 1;
	for (int i = 0 ; i < line_count; i++) {

		if(parser(file_line[i]) == -1){
			printf("line: %d\n", i);
			printf("%s\n", file_line[i]);
			printf("error parsing file\n");
			return -1;
		}

		j++;
	}

	//  check if all required arguments are present
	if (arg_1 == false || arg_2 == false || arg_3 == false || arg_4 == false
	|| arg_5 == false || arg_6 == false || arg_7 == false) {
		printf("missing variables in txt file\n");
		return -1;
	}
	return 0;
}
