import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class AppService {

  private apiUrl = 'http://localhost:8080';

  constructor(private http: HttpClient) { }

  getVaccinationData(): Observable<any> {
    return this.http.get(`${this.apiUrl}/vaccination`);
  }

  getDailySum(): Observable<any> {
    return this.http.get(`${this.apiUrl}/daily-sum-chart`);
  }

  getPerCountry(): Observable<any> {
    return this.http.get(`${this.apiUrl}/per-country-chart`);
  }

  getMarketShares(): Observable<any> {
    return this.http.get(`${this.apiUrl}/market-shares-chart`);
  }
}
