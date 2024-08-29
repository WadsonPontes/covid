import { Component, OnInit } from '@angular/core';
import { AppService } from 'src/app/services/app.service';

@Component({
  selector: 'app-per-country-chart',
  templateUrl: './per-country-chart.component.html',
  styleUrls: ['./per-country-chart.component.scss']
})
export class PerCountryChartComponent implements OnInit {
  public data: any;
  public maxCountries: number = 500; // Limitar o número de países exibidos

  public graph = {
    data: [
        {
          x: [],
          y: [],
          width: 0.90,
          type: 'bar',
          text: [],
          textposition: 'auto',
          hoverinfo: 'none',
          marker: {
            color: 'blue',
            line: {
              color: 'blue',
              width: 0.1
            }
          }
        }
    ],
    layout: {
      title: {
        text: 'Percentage of people fully immunized by country',
        x: 0, // Alinhamento à esquerda
        xref: 'paper', // Usar coordenadas relativas ao papel
        xanchor: 'left', // Ancorar à esquerda
      },
      width: 7680,
      height: 500,
      barmode: 'stack'
    },
    config: { responsive: true }
  };

  constructor(private appService: AppService) { }

  ngOnInit(): void {
    this.appService.getPerCountry().subscribe(
      (response) => {
        this.data = response;

        let y = this.data.y.slice(0, this.maxCountries);

        this.graph.data[0].x = this.data.x.slice(0, this.maxCountries);
        this.graph.data[0].y = y;
        this.graph.data[0].text = y.map(String);
      },
      (error) => {
        console.error('Error retrieving data:', error);
      }
    );
  }

}
