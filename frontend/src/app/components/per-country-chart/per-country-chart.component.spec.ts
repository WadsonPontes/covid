import { ComponentFixture, TestBed } from '@angular/core/testing';

import { PerCountryChartComponent } from './per-country-chart.component';

describe('PerCountryChartComponent', () => {
  let component: PerCountryChartComponent;
  let fixture: ComponentFixture<PerCountryChartComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ PerCountryChartComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(PerCountryChartComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
