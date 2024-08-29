package com.wadson.dto;

import java.time.LocalDate;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
public class DailyVaccinationSumDTO {
    private LocalDate vaccinationDate;
    private Double totalDailyVaccinationsPerMillion;
}
