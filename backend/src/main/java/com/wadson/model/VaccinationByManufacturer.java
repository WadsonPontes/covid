package com.wadson.model;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
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
    
	@ManyToOne
    @JoinColumn(name = "country_id", nullable = false)
    private Country country;
    
    @Column(nullable = false)
    private LocalDate vaccinationDate;
    
    @ManyToOne
    @JoinColumn(name = "vaccine_id", nullable = false)
    private Vaccine vaccine;
    
    @Column(nullable = false)
    private int totalVaccinations;
}
