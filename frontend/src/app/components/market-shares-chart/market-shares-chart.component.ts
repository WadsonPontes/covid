import { Component, OnInit } from '@angular/core';
import { AppService } from 'src/app/services/app.service';

@Component({
  selector: 'app-market-shares-chart',
  templateUrl: './market-shares-chart.component.html',
  styleUrls: ['./market-shares-chart.component.scss']
})
export class MarketSharesChartComponent implements OnInit {
  public data: any;

  public graph = {
    data: [
        {
          values: [],
          labels: [],
          textinfo: "label+percent",
          type: 'pie'
        }
    ],
    layout: {
      title: 'Market Shares'
    },
    config: { responsive: true }
  };

  constructor(private appService: AppService) { }

  ngOnInit(): void {
    this.appService.getMarketShares().subscribe(
      (response) => {
        this.data = response;
        console.log(response);
        this.graph.data[0].values = this.data.values;
        this.graph.data[0].labels = this.data.labels;
      },
      (error) => {
        console.error('Error retrieving data:', error);
      }
    );
  }

}
