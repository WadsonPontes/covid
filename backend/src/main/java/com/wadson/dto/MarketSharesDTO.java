package com.wadson.dto;

import java.util.List;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
public class MarketSharesDTO {
	private List<Double> values;  // Percentagem do mercado
    private List<String> labels;   // Lista de vacinas
}
