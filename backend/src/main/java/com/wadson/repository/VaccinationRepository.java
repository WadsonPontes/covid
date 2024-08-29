package com.wadson.repository;

import java.util.List;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.domain.Pageable;

import com.wadson.dto.DailyVaccinationSumDTO;
import com.wadson.model.Vaccination;

public interface VaccinationRepository extends JpaRepository<Vaccination, Long> {
	@Query(value = "SELECT v FROM Vaccination v ORDER BY v.id ASC")
    List<Vaccination> findAllWithLimit(Pageable pageable);
	
	@Query("SELECT new com.wadson.dto.DailyVaccinationSumDTO(v.vaccinationDate, SUM(v.dailyVaccinationsPerMillion)) " +
	           "FROM Vaccination v " +
	           "GROUP BY v.vaccinationDate " +
	           "ORDER BY v.vaccinationDate")
    List<DailyVaccinationSumDTO> findDailyVaccinationSum();
}
