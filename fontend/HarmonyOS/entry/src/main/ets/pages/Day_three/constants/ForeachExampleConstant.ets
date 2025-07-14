export interface PayDataInterface{
  OrderName:string
  OrderPrice:number
  OrderTime:Date
}
export class PayData{
  private _PayData: Array<PayDataInterface> = [
    {
      OrderName: "买口红",
      OrderPrice: 399.00,
      OrderTime: new Date("2024/5/11")
    },
    {
      OrderName: "买花",
      OrderPrice: 99.00,
      OrderTime: new Date("2024/5/12")
    },
    {
      OrderName: "买手机",
      OrderPrice: 9999.00,
      OrderTime: new Date("2024/5/13")
    }
  ]

  public get PayData(): Array<PayDataInterface> {
    return this._PayData
  }
}

