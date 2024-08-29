package com.wadson.dto;

import java.time.LocalDate;
import java.util.List;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
public class DailyVaccinationSumChartDTO {
    private List<LocalDate> x;  // Lista de datas
    private List<Double> y;   // Lista de somas de vacinas diárias por milhão
}
