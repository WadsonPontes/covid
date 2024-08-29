#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 1024
#define MAX_COUNTRIES 500
#define MAX_VACCINES 50

typedef struct {
    char name[255];
    int id;
} Country;

typedef struct {
    char name[255];
    int id;
} Vaccine;

int find_country(Country countries[], int country_count, const char *country_name);
int add_country(Country countries[], int *country_count, const char *country_name, FILE *country_file);
int find_vaccine(Vaccine vaccines[], int vaccine_count, const char *vaccine_name);
int add_vaccine(Vaccine vaccines[], int *vaccine_count, const char *vaccine_name, FILE *vaccine_file);

int main() {
    FILE *file = fopen("country_vaccinations_by_manufacturer.csv", "r");
    if (!file) {
        fprintf(stderr, "Não foi possível abrir o arquivo CSV.\n");
        return 1;
    }

    FILE *country_file = fopen("country.sql", "w");
    FILE *vaccine_file = fopen("vaccine.sql", "w");
    FILE *vaccination_file = fopen("vaccination_by_manufacturer.sql", "w");

    if (!country_file || !vaccine_file || !vaccination_file) {
        fprintf(stderr, "Não foi possível abrir os arquivos de saída.\n");
        return 1;
    }

    Country countries[MAX_COUNTRIES];
    int country_count = 0;

    Vaccine vaccines[MAX_VACCINES];
    int vaccine_count = 0;

    char line[LINE_LENGTH];
    int id_counter = 1;
    
    while (fgets(line, LINE_LENGTH, file)) {
        char *country_name = strtok(line, ",");
        char *date = strtok(NULL, ",");
        char *vaccine_name = strtok(NULL, ",");
        char *total_vaccinations_str = strtok(NULL, ",");

        int total_vaccinations = atoi(total_vaccinations_str);

        int country_id = find_country(countries, country_count, country_name);
        if (country_id == -1) {
            country_id = add_country(countries, &country_count, country_name, country_file);
        }

        int vaccine_id = find_vaccine(vaccines, vaccine_count, vaccine_name);
        if (vaccine_id == -1) {
            vaccine_id = add_vaccine(vaccines, &vaccine_count, vaccine_name, vaccine_file);
        }

        fprintf(vaccination_file,
            "INSERT INTO public.vaccination_by_manufacturer (id, total_vaccinations, vaccination_date, country_id, vaccine_id) "
            "VALUES (%d, %d, '%s', %d, %d);\n",
            id_counter++, total_vaccinations, date, country_id, vaccine_id);
    }

    fclose(file);
    fclose(country_file);
    fclose(vaccine_file);
    fclose(vaccination_file);

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

int add_country(Country countries[], int *country_count, const char *country_name, FILE *country_file) {
    int id = *country_count + 1;
    strncpy(countries[*country_count].name, country_name, 255);
    countries[*country_count].id = id;
    (*country_count)++;
    fprintf(country_file, "INSERT INTO public.country (id, iso_code, name) VALUES (%d, 'ISO_CODE', '%s');\n", id, country_name);
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
