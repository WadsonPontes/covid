package com.wadson.controller;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import com.wadson.model.Vaccination;
import com.wadson.service.VaccinationService;

@RestController
public class VaccinationController {
	
	@Autowired
	private VaccinationService vaccinationService;
	
	@GetMapping(value = "/vaccination", produces = { MediaType.APPLICATION_JSON_VALUE })
	public List<Vaccination> getVaccinationData() {
		return vaccinationService.getAll();
	}
}
