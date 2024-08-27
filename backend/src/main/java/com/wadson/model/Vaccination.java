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
    
    @ManyToOne
    @JoinColumn(name = "country_id", nullable = false)
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
    
    @ManyToMany
    @JoinTable(
        name = "vaccination_vaccines",
        joinColumns = @JoinColumn(name = "vaccination_id"),
        inverseJoinColumns = @JoinColumn(name = "vaccine_id")
    )
    private List<Vaccine> vaccines;
    
    @ManyToOne
    @JoinColumn(name = "source_id", nullable = false)
    private Source source;
}
