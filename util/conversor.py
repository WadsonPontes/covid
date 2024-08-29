import csv

MAX_COUNTRIES = 500
MAX_VACCINES = 50
MAX_SOURCE = 500

class Country:
    def __init__(self, name, iso_code, id):
        self.name = name
        self.iso_code = iso_code
        self.id = id

class Vaccine:
    def __init__(self, name, id):
        self.name = name
        self.id = id

class Source:
    def __init__(self, name, website, id):
        self.name = name
        self.website = website
        self.id = id

def escape_single_quotes(value):
    return value.replace("'", "''")

def find_country(countries, country_name):
    for country in countries:
        if country.name == country_name:
            return country.id
    return -1

def add_country(countries, country_name, iso_code, country_file):
    id = len(countries) + 1
    new_country = Country(country_name, iso_code, id)
    countries.append(new_country)
    country_file.write(f"INSERT INTO public.country (id, iso_code, name) VALUES ({id}, '{iso_code}', '{country_name}');\n")
    return id

def find_vaccine(vaccines, vaccine_name):
    for vaccine in vaccines:
        if vaccine.name == vaccine_name:
            return vaccine.id
    return -1

def add_vaccine(vaccines, vaccine_name, vaccine_file):
    id = len(vaccines) + 1
    new_vaccine = Vaccine(vaccine_name, id)
    vaccines.append(new_vaccine)
    vaccine_file.write(f"INSERT INTO public.vaccine (id, name) VALUES ({id}, '{vaccine_name}');\n")
    return id

def find_source(sources, source_name):
    for source in sources:
        if source.name == source_name:
            return source.id
    return -1

def add_source(sources, source_name, source_website, source_file):
    id = len(sources) + 1
    new_source = Source(source_name, source_website, id)
    sources.append(new_source)
    source_file.write(f"INSERT INTO public.source (id, website, name) VALUES ({id}, '{source_website}', '{source_name}');\n")
    return id

def main():
    with open('../csv/country_vaccinations.csv', 'r') as country_vacc_file, \
         open('../csv/country_vaccinations_by_manufacturer.csv', 'r') as manufacturer_vacc_file, \
         open('../sql/country.sql', 'w') as country_file, \
         open('../sql/vaccine.sql', 'w') as vaccine_file, \
         open('../sql/source.sql', 'w') as source_file, \
         open('../sql/vaccination.sql', 'w') as vaccination_file, \
         open('../sql/vaccination_by_manufacturer.sql', 'w') as vaccination_by_manufacturer_file, \
         open('../sql/vaccination_vaccines.sql', 'w') as vaccination_vaccines_file:

        countries = []
        vaccines = []
        sources = []

        vaccination_by_manufacturer_count = 0
        vaccination_count = 0

        # Process country_vaccinations.csv
        reader = csv.reader(country_vacc_file)
        next(reader)  # Skip header
        for row in reader:
            country_name = escape_single_quotes(row[0])
            iso_code = row[1][-3:]
            vaccination_date = row[2]
            total_vaccinations_str = row[3] if row[3] != "" else "NULL"
            people_vaccinated_str = row[4] if row[4] != "" else "NULL"
            people_fully_vaccinated_str = row[5] if row[5] != "" else "NULL"
            daily_vaccinations_raw_str = row[6] if row[6] != "" else "NULL"
            daily_vaccinations_str = row[7] if row[7] != "" else "NULL"
            total_vaccinations_per_hundred_str = row[8] if row[8] != "" else "NULL"
            people_vaccinated_per_hundred_str = row[9] if row[9] != "" else "NULL"
            people_fully_vaccinated_per_hundred_str = row[10] if row[10] != "" else "NULL"
            daily_vaccinations_per_million_str = row[11] if row[11] != "" else "NULL"
            vaccine_list = escape_single_quotes(row[12].strip('"'))
            source_name = escape_single_quotes(row[13])
            source_website = escape_single_quotes(row[14].strip()) if row[14] else ""

            country_id = find_country(countries, country_name)
            if country_id == -1:
                country_id = add_country(countries, country_name, iso_code, country_file)

            vaccine_names = vaccine_list.split(", ")
            for vaccine_name in vaccine_names:
                vaccine_id = find_vaccine(vaccines, vaccine_name)
                if vaccine_id == -1:
                    vaccine_id = add_vaccine(vaccines, vaccine_name, vaccine_file)
                vaccination_vaccines_file.write(
                    f"INSERT INTO public.vaccination_vaccines (vaccination_id, vaccine_id) "
                    f"VALUES ({vaccination_count + 1}, {vaccine_id});\n")

            source_id = find_source(sources, source_name)
            if source_id == -1:
                source_id = add_source(sources, source_name, source_website, source_file)

            vaccination_file.write(
                f"INSERT INTO public.vaccination (id, daily_vaccinations, daily_vaccinations_per_million, "
                f"daily_vaccinations_raw, people_fully_vaccinated, people_fully_vaccinated_per_hundred, "
                f"people_vaccinated, people_vaccinated_per_hundred, total_vaccinations, total_vaccinations_per_hundred, "
                f"vaccination_date, country_id, source_id) "
                f"VALUES ({vaccination_count + 1}, {daily_vaccinations_str}, {daily_vaccinations_per_million_str}, "
                f"{daily_vaccinations_raw_str}, {people_fully_vaccinated_str}, {people_fully_vaccinated_per_hundred_str}, "
                f"{people_vaccinated_str}, {people_vaccinated_per_hundred_str}, {total_vaccinations_str}, "
                f"{total_vaccinations_per_hundred_str}, '{vaccination_date}', {country_id}, {source_id});\n")
            vaccination_count += 1

        # Process country_vaccinations_by_manufacturer.csv
        reader = csv.reader(manufacturer_vacc_file)
        next(reader)  # Skip header
        for row in reader:
            country_name = row[0]
            vaccination_date = row[1]
            vaccine_name = row[2]
            total_vaccinations_str = row[3]

            country_id = find_country(countries, country_name)
            if country_id == -1:
                country_id = add_country(countries, country_name, "-", country_file)

            vaccine_id = find_vaccine(vaccines, vaccine_name)
            if vaccine_id == -1:
                vaccine_id = add_vaccine(vaccines, vaccine_name, vaccine_file)

            vaccination_by_manufacturer_file.write(
                f"INSERT INTO public.vaccination_by_manufacturer (id, total_vaccinations, vaccination_date, country_id, vaccine_id) "
                f"VALUES ({vaccination_by_manufacturer_count + 1}, {total_vaccinations_str}, '{vaccination_date}', {country_id}, {vaccine_id});\n")
            vaccination_by_manufacturer_count += 1

if __name__ == "__main__":
    main()
