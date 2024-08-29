package com.wadson.dto;

import java.util.List;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
public class PercentageVaccinatedByCountryDTO {
	private List<String> x;  // Lista de nomes de países
    private List<Double> y;   // Lista dos valores máximos de vacinação completa por 100 habitantes
}
