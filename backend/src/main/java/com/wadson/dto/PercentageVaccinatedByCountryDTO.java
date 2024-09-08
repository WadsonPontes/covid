package com.wadson.dto;

import java.util.List;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
public class PercentageVaccinatedByCountryDTO {
	private List<Double> x;  // Lista dos valores máximos de vacinação completa por 100 habitantes
    private List<String> y;   // Lista de nomes de países
}
