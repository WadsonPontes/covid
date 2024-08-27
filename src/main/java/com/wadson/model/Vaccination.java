package com.wadson.model;

import java.util.List;

import lombok.Data;
import lombok.NoArgsConstructor;
import javax.persistence.*;
import java.time.LocalDate;

@Entity
@Table(name = "vaccination")
@Data
@NoArgsConstructor
public class Vaccination {
	@Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    
    @Column(nullable = false)
    private Country country;
    
    @Column(nullable = false)
    private LocalDate vaccinationDate;
    
    @Column(nullable = true)
    private Double totalVaccinations;
    
    @Column(nullable = true)
    private Double peopleVaccinated;
    
    @Column(nullable = true)
    private Double peopleFullyVaccinated;
    
    @Column(nullable = true)
    private Double dailyVaccinationsRaw;
    
    @Column(nullable = true)
    private Double dailyVaccinations;
    
    @Column(nullable = true)
    private Double totalVaccinationsPerHundred;
    
    @Column(nullable = true)
    private Double peopleVaccinatedPerHundred;
    
    @Column(nullable = true)
    private Double peopleFullyVaccinatedPerHundred;
    
    @Column(nullable = true)
    private Double dailyVaccinationsPerMillion;
    
    @Column(nullable = false)
    private List<Vaccine> vaccines;
    
    @Column(nullable = false)
    private Source source;
}
