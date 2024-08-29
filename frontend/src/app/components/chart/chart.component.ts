import { Component, OnInit } from '@angular/core';
import { AppService } from 'src/app/services/app.service';

@Component({
  selector: 'app-chart',
  templateUrl: './chart.component.html',
  styleUrls: ['./chart.component.scss']
})
export class ChartComponent implements OnInit {
  public data: any;

  public graph = {
    data: [
        {
          x: [],
          y: [],
          type: 'scatter',
          mode: 'lines+points',
          marker: {color: 'red'}
        }
    ],
    layout: {width: 1280, height: 720, title: 'Daily COVID-19 vaccine doses administered per million people'}
  };

  constructor(private appService: AppService) { }

  ngOnInit(): void {
    this.appService.getDailySum().subscribe(
      (response) => {
        this.data = response;
        this.graph.data[0].x = this.data.x;
        this.graph.data[0].y = this.data.y;
      },
      (error) => {
        console.error('Error retrieving data:', error);
      }
    );
  }

}
