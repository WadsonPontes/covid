package com.wadson.repository;

import java.time.LocalDate;
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
	
	@Query("SELECT v.vaccinationDate FROM Vaccination v GROUP BY v.vaccinationDate ORDER BY v.vaccinationDate")
    List<LocalDate> findDistinctDates(); // Retorna uma lista de datas distintas

    @Query("SELECT SUM(v.dailyVaccinationsPerMillion) FROM Vaccination v GROUP BY v.vaccinationDate ORDER BY v.vaccinationDate")
    List<Double> findSumDailyVaccinations(); // Retorna a soma das vacinações diárias por milhão para cada data
    
    @Query("SELECT c.name " +
            "FROM Vaccination v " +
            "JOIN v.country c " +
            "GROUP BY c.name " +
            "ORDER BY MAX(v.peopleFullyVaccinatedPerHundred) ASC")
    List<String> findCountryName();
    
    @Query("SELECT MAX(v.peopleFullyVaccinatedPerHundred) as num_max FROM Vaccination v GROUP BY v.country ORDER BY num_max ASC")
    List<Double> findSumByCountry();
    
    @Query("SELECT v.name FROM VaccinationByManufacturer vbm "
    		+ "JOIN vbm.vaccine v "
    		+ "GROUP BY v.name "
    		+ "ORDER BY SUM(vbm.totalVaccinations) DESC")
    List<String> findVaccineName();
    
    @Query("SELECT SUM(vbm.totalVaccinations) AS total FROM VaccinationByManufacturer vbm "
    		+ "GROUP BY vbm.vaccine "
    		+ "ORDER BY total DESC")
    List<Double> findVaccinationByManufacturer();
}
