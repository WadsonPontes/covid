import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { HttpClientModule } from '@angular/common/http';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { DailySumChartComponent } from './components/daily-sum-chart/daily-sum-chart.component';
import { PerCountryChartComponent } from './components/per-country-chart/per-country-chart.component';
import { MarketSharesChartComponent } from './components/market-shares-chart/market-shares-chart.component';

import * as PlotlyJS from 'plotly.js-dist-min';
import { PlotlyModule } from 'angular-plotly.js';


PlotlyModule.plotlyjs = PlotlyJS;

@NgModule({
  declarations: [
    AppComponent,
    DailySumChartComponent,
    PerCountryChartComponent,
    MarketSharesChartComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    HttpClientModule,
    PlotlyModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
