package com.wadson.model;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;
import java.time.LocalDate;

import lombok.Data;
import lombok.NoArgsConstructor;

@Entity
@Table(name = "vaccination_by_manufacturer")
@Data
@NoArgsConstructor
public class VaccinationByManufacturer {
	@Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    
    @Column(nullable = false)
    private Country country;
    
    @Column(nullable = false)
    private LocalDate vaccinationDate;
    
    @Column(nullable = false)
    private Vaccine vaccine;
    
    @Column(nullable = false)
    private int totalVaccinations;
}
