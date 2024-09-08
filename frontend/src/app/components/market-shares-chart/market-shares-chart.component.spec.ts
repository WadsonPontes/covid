import { ComponentFixture, TestBed } from '@angular/core/testing';

import { MarketSharesChartComponent } from './market-shares-chart.component';

describe('MarketSharesChartComponent', () => {
  let component: MarketSharesChartComponent;
  let fixture: ComponentFixture<MarketSharesChartComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ MarketSharesChartComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(MarketSharesChartComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
