package com.wadson.service;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.wadson.model.Vaccination;
import com.wadson.repository.VaccinationRepository;

@Service
public class VaccinationService {
	@Autowired
	private VaccinationRepository vaccinationRepository;
	
	public List<Vaccination> getAll() {
        return vaccinationRepository.findAll();
    }
}
