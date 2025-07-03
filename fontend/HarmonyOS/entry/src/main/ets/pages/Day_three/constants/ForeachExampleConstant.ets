export interface PayDataInterface{
  OrderName:string
  OrderPrice:number
  OrderTime:Date
}
export class PayData{
  PayData:Array<PayDataInterface>=[
    {
      OrderName:"买口红",
      OrderPrice:399.00,
      OrderTime:new Date("2024/5/11")
    },
    {
      OrderName: "买口红",
      OrderPrice: 399.00,
      OrderTime: new Date("2024/5/11")
    },
    {
      OrderName:"买口红",
      OrderPrice:399.00,
      OrderTime:new Date("2024/5/11")
    }
  ]
}

