#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 2048
#define MAX_COUNTRIES 500
#define MAX_VACCINES 50
#define MAX_SOURCE 500

typedef struct {
    char name[255];
    char iso_code[10];
    int id;
} Country;

typedef struct {
    char name[255];
    int id;
} Vaccine;

typedef struct {
    char website[255];
    char name[255];
    int id;
} Source;


int find_country(Country countries[], int country_count, const char *country_name);
int add_country(Country countries[], int *country_count, const char *country_name, const char *iso_code, FILE *country_file);
int find_vaccine(Vaccine vaccines[], int vaccine_count, const char *vaccine_name);
int add_vaccine(Vaccine vaccines[], int *vaccine_count, const char *vaccine_name, FILE *vaccine_file);
int find_source(Source source[], int source_count, const char *source_name);
int add_source(Source source[], int *source_count, const char *source_name, const char *source_website, FILE *source_file);
char* custom_strtok(char** str, const char* delim);

int main() {
    FILE *country_vacc_file = fopen("../csv/country_vaccinations.csv", "r");
    FILE *manufacturer_vacc_file = fopen("../csv/country_vaccinations_by_manufacturer.csv", "r");
    if (!country_vacc_file || !manufacturer_vacc_file) {
        fprintf(stderr, "Não foi possível abrir os arquivos CSV.\n");
        return 1;
    }

    FILE *country_file = fopen("../sql/country.sql", "w");
    FILE *vaccine_file = fopen("../sql/vaccine.sql", "w");
    FILE *source_file = fopen("../sql/source.sql", "w");
    FILE *vaccination_file = fopen("../sql/vaccination.sql", "w");
    FILE *vaccination_by_manufacturer_file = fopen("../sql/vaccination_by_manufacturer.sql", "w");
    FILE *vaccination_vaccines_file = fopen("../sql/vaccination_vaccines.sql", "w");

    if (!country_file || !vaccine_file || !source_file || !vaccination_file || !vaccination_by_manufacturer_file || !vaccination_vaccines_file) {
        fprintf(stderr, "Não foi possível abrir os arquivos de saída.\n");
        return 1;
    }

    Country countries[MAX_COUNTRIES];
    int country_count = 0;

    Vaccine vaccines[MAX_VACCINES];
    int vaccine_count = 0;

    Source sources[MAX_SOURCE];
    int source_count = 0;

    int vaccination_vaccines_count = 0;

    int vaccination_by_manufacturer_count = 0;

    int vaccination_count = 0;

    char *line_original = (char*) malloc(LINE_LENGTH * sizeof(char));

    // Processar country_vaccinations.csv
    fgets(line_original, LINE_LENGTH, country_vacc_file); // Ignorar cabeçalho
    while (fgets(line_original, LINE_LENGTH, country_vacc_file)) {
        char *line = strdup(line_original);
        char *country_name = custom_strtok(&line, ",");
        char *iso_code = custom_strtok(&line, ",");
        char *vaccination_date = custom_strtok(&line, ",");
        char *total_vaccinations_str = custom_strtok(&line, ",");
        char *people_vaccinated_str = custom_strtok(&line, ",");
        char *people_fully_vaccinated_str = custom_strtok(&line, ",");
        char *daily_vaccinations_raw_str = custom_strtok(&line, ",");
        char *daily_vaccinations_str = custom_strtok(&line, ",");
        char *total_vaccinations_per_hundred_str = custom_strtok(&line, ",");
        char *people_vaccinated_per_hundred_str = custom_strtok(&line, ",");
        char *people_fully_vaccinated_per_hundred_str = custom_strtok(&line, ",");
        char *daily_vaccinations_per_million_str = custom_strtok(&line, ",");
        if (line != NULL) ++line; // Tira as aspas
        char *vaccine_list = custom_strtok(&line, "\"");
        if (line != NULL) ++line; // Remove a virgula
        char *source_name = custom_strtok(&line, ",");
        char *source_website = custom_strtok(&line, ",");
        if (source_website != NULL && strlen(source_website) > 0) {
            source_website[strlen(source_website)-1] = '\0'; // Remove o \n
        }
    printf("'%s'\n", vaccine_list);
        int country_id = find_country(countries, country_count, country_name);
        if (country_id == -1) {
            country_id = add_country(countries, &country_count, country_name, iso_code, country_file);
        }

        char *vaccine_name = strtok(vaccine_list, ", ");
        while (vaccine_name != NULL) {
            int vaccine_id = find_vaccine(vaccines, vaccine_count, vaccine_name);
            if (vaccine_id == -1) {
                vaccine_id = add_vaccine(vaccines, &vaccine_count, vaccine_name, vaccine_file);
            }
            fprintf(vaccination_vaccines_file,
                "INSERT INTO public.vaccination_vaccines (vaccination_id, vaccine_id) "
                "VALUES (%d, %d);\n",
                ++vaccination_vaccines_count, vaccine_id);
            vaccine_name = strtok(NULL, ", ");
        }

        int source_id = find_source(sources, source_count, source_name);
        if (source_id == -1) {
            source_id = add_source(sources, &source_count, source_name, source_website, source_file);
        }

        fprintf(vaccination_file,
            "INSERT INTO public.vaccination (id, daily_vaccinations, daily_vaccinations_per_million, "
            "daily_vaccinations_raw, people_fully_vaccinated, people_fully_vaccinated_per_hundred, "
            "people_vaccinated, people_vaccinated_per_hundred, total_vaccinations, total_vaccinations_per_hundred, "
            "vaccination_date, country_id, source_id) "
            "VALUES (%d, %s, %s, %s, %s, %s, %s, %s, %s, %s, '%s', %d, %d);\n",
            ++vaccination_count, daily_vaccinations_str, daily_vaccinations_per_million_str,
            daily_vaccinations_raw_str, people_fully_vaccinated_str, people_fully_vaccinated_per_hundred_str,
            people_vaccinated_str, people_vaccinated_per_hundred_str, total_vaccinations_str,
            total_vaccinations_per_hundred_str, vaccination_date, country_id, source_id);
    }

    fclose(country_vacc_file);

    // Processar country_vaccinations_by_manufacturer.csv
    fgets(line_original, LINE_LENGTH, manufacturer_vacc_file); // Ignorar cabeçalho
    while (fgets(line_original, LINE_LENGTH, manufacturer_vacc_file)) {
        char *line = strdup(line_original);
        char *country_name = custom_strtok(&line, ",");
        char *vaccination_date = custom_strtok(&line, ",");
        char *vaccine_name = custom_strtok(&line, ",");
        char *total_vaccinations_str = custom_strtok(&line, ",");

        int country_id = find_country(countries, country_count, country_name);
        if (country_id == -1) {
            country_id = add_country(countries, &country_count, country_name, "-", country_file);
        }


        int vaccine_id = find_vaccine(vaccines, vaccine_count, vaccine_name);
        if (vaccine_id == -1) {
            vaccine_id = add_vaccine(vaccines, &vaccine_count, vaccine_name, vaccine_file);
        }

        fprintf(vaccination_by_manufacturer_file,
            "INSERT INTO public.vaccination_by_manufacturer (id, total_vaccinations, vaccination_date, country_id, vaccine_id) "
            "VALUES (%d, %s, '%s', %d, %d);\n",
            ++vaccination_by_manufacturer_count, total_vaccinations_str, vaccination_date, country_id, vaccine_id);
    }

    if(line_original != NULL) free(line_original);

    fclose(manufacturer_vacc_file);

    fclose(country_file);
    fclose(vaccine_file);
    fclose(source_file);
    fclose(vaccination_file);
    fclose(vaccination_by_manufacturer_file);
    fclose(vaccination_vaccines_file);

    return 0;
}

int find_country(Country countries[], int country_count, const char *country_name) {
    for (int i = 0; i < country_count; i++) {
        if (strcmp(countries[i].name, country_name) == 0) {
            return countries[i].id;
        }
    }
    return -1;
}

int add_country(Country countries[], int *country_count, const char *country_name, const char *iso_code, FILE *country_file) {
    int id = *country_count + 1;
    strncpy(countries[*country_count].name, country_name, 255);
    strncpy(countries[*country_count].iso_code, iso_code, 10);
    countries[*country_count].id = id;
    (*country_count)++;
    fprintf(country_file, "INSERT INTO public.country (id, iso_code, name) VALUES (%d, '%s', '%s');\n", id, iso_code, country_name);
    return id;
}

int find_vaccine(Vaccine vaccines[], int vaccine_count, const char *vaccine_name) {
    for (int i = 0; i < vaccine_count; i++) {
        if (strcmp(vaccines[i].name, vaccine_name) == 0) {
            return vaccines[i].id;
        }
    }
    return -1;
}

int add_vaccine(Vaccine vaccines[], int *vaccine_count, const char *vaccine_name, FILE *vaccine_file) {
    int id = *vaccine_count + 1;
    strncpy(vaccines[*vaccine_count].name, vaccine_name, 255);
    vaccines[*vaccine_count].id = id;
    (*vaccine_count)++;
    fprintf(vaccine_file, "INSERT INTO public.vaccine (id, name) VALUES (%d, '%s');\n", id, vaccine_name);
    return id;
}

int find_source(Source sources[], int source_count, const char *source_name) {
    for (int i = 0; i < source_count; i++) {
        if (strcmp(sources[i].name, source_name) == 0) {
            return sources[i].id;
        }
    }
    return -1;
}

int add_source(Source sources[], int *source_count, const char *source_name, const char *source_website, FILE *source_file) {
    int id = *source_count + 1;
    strncpy(sources[*source_count].name, source_name, 255);
    strncpy(sources[*source_count].website, source_website, 10);
    sources[*source_count].id = id;
    (*source_count)++;
    fprintf(source_file, "INSERT INTO public.country (id, website, name) VALUES (%d, '%s', '%s');\n", id, source_website, source_name);
    return id;
}

// Função para obter o próximo token, considerando campos vazios
char* custom_strtok(char** str, const char* delim) {
    if (*str == NULL) return "NULL";

    // Encontrar a primeira ocorrência de um delimitador
    char *end = strpbrk(*str, delim);

    // Se não encontrar delimitador, retornar o token restante
    if (end == NULL) {
        char *token = *str;
        *str = NULL;
        return token;
    }

    // Se um delimitador for encontrado, pode haver campos vazios
    *end = '\0';  // Termina o token atual
    char *token = *str;
    *str = end + 1;  // Avança para o próximo token

    // Se o token for uma string vazia (um delimitador seguido imediatamente de outro)
    if (token == NULL || strlen(token) == 0) {
        return "NULL";
    }

    return token;
}