import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-chart',
  templateUrl: './chart.component.html',
  styleUrls: ['./chart.component.scss']
})
export class ChartComponent implements OnInit {

  public graph = {
    data: [
        { x: [1, 2, 3], y: [2, 6, 10], type: 'scatter', mode: 'lines+points', marker: {color: 'red'} },
        { x: [1, 2, 3], y: [2, 5, 10], type: 'bar' },
    ],
    layout: {width: 320, height: 240, title: 'A Fancy Plot'}
  };

  constructor() { }

  ngOnInit(): void {
  }

}
