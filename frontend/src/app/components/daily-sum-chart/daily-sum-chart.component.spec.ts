import { ComponentFixture, TestBed } from '@angular/core/testing';

import { DailySumChartComponent } from './daily-sum-chart.component';

describe('DailySumChartComponent', () => {
  let component: DailySumChartComponent;
  let fixture: ComponentFixture<DailySumChartComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ DailySumChartComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(DailySumChartComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
