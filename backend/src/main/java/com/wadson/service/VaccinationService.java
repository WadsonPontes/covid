package com.wadson.service;

import java.time.LocalDate;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.data.domain.PageRequest;

import com.wadson.dto.DailyVaccinationSumChartDTO;
import com.wadson.dto.DailyVaccinationSumDTO;
import com.wadson.dto.PercentageVaccinatedByCountryDTO;
import com.wadson.dto.MarketSharesDTO;
import com.wadson.model.Vaccination;
import com.wadson.repository.VaccinationRepository;

@Service
public class VaccinationService {
	@Autowired
	private VaccinationRepository vaccinationRepository;
	
	public List<Vaccination> getAll() {
        return vaccinationRepository.findAll();
    }
	
	public List<Vaccination> getAllWithLimit() {
		return vaccinationRepository.findAllWithLimit(PageRequest.of(0, 100));
    }
	
	public List<DailyVaccinationSumDTO> getDailyVaccinationSum() {
        return vaccinationRepository.findDailyVaccinationSum();
    }
	
	public DailyVaccinationSumChartDTO getDailyVaccinationSumChart() {
        List<LocalDate> dates = vaccinationRepository.findDistinctDates();
        List<Double> sums = vaccinationRepository.findSumDailyVaccinations();

        return new DailyVaccinationSumChartDTO(dates, sums);
    }
	
	public PercentageVaccinatedByCountryDTO getPercentageVaccinatedByCountryChart() {
        List<String> countries = vaccinationRepository.findCountryName();
        List<Double> sums = vaccinationRepository.findSumByCountry();

        return new PercentageVaccinatedByCountryDTO(sums, countries);
    }
	
	public MarketSharesDTO getMarketSharesChart() {
        List<String> vaccine = vaccinationRepository.findVaccineName();
        List<Double> sums = vaccinationRepository.findVaccinationByManufacturer();

        return new MarketSharesDTO(sums, vaccine);
    }
}
