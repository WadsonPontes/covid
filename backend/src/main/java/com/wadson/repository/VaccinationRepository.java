package com.wadson.repository;

import org.springframework.data.jpa.repository.JpaRepository;

import com.wadson.model.Vaccination;

public interface VaccinationRepository extends JpaRepository<Vaccination, Long> {

}
