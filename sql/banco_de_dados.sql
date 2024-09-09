CREATE TABLE public.country (
    id bigint NOT NULL,
    iso_code character varying(255) NOT NULL,
    name character varying(255) NOT NULL
);

CREATE TABLE public.source (
    id bigint NOT NULL,
    name character varying(255) NOT NULL,
    website character varying(255)
);

CREATE TABLE public.vaccination (
    id bigint NOT NULL,
    daily_vaccinations double precision,
    daily_vaccinations_per_million double precision,
    daily_vaccinations_raw double precision,
    people_fully_vaccinated double precision,
    people_fully_vaccinated_per_hundred double precision,
    people_vaccinated double precision,
    people_vaccinated_per_hundred double precision,
    total_vaccinations double precision,
    total_vaccinations_per_hundred double precision,
    vaccination_date date NOT NULL,
    country_id bigint NOT NULL,
    source_id bigint NOT NULL
);

CREATE TABLE public.vaccination_by_manufacturer (
    id bigint NOT NULL,
    total_vaccinations integer NOT NULL,
    vaccination_date date NOT NULL,
    country_id bigint NOT NULL,
    vaccine_id bigint NOT NULL
);

CREATE TABLE public.vaccination_vaccines (
    vaccination_id bigint NOT NULL,
    vaccine_id bigint NOT NULL
);

CREATE TABLE public.vaccine (
    id bigint NOT NULL,
    name character varying(255) NOT NULL
);

