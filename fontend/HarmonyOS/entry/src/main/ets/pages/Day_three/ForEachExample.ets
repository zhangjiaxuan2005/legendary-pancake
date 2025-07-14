import { PayData, PayDataInterface } from './constants/ForeachExampleConstant'

@Entry
@Component
struct ForEachExample {
  public payItemData: Array<PayDataInterface> = []

  aboutToAppear(): void {
    const payItemDataObject = new PayData()
    this.payItemData = payItemDataObject.PayData
  }

  build() {
    Column({ space: 8 }) {
      ForEach(this.payItemData, (item: PayDataInterface) => {
        PayListItem({ context: item })
      }, (item: PayDataInterface) => JSON.stringify(item))
    }
    .width("100%")
  }
}

@ComponentV2
struct PayListItem {
  @Param @Require context: PayDataInterface

  build() {
    Column({ space: 6 }) {
      Text(this.context.OrderName)
        .fontSize(26)
      Row() {
        Text('￥' + this.context.OrderPrice.toFixed(2).toString())
          .fontColor(Color.Red)
          .fontSize(18)
        Blank()
          .layoutWeight(1)
        Text(this.context.OrderTime.toLocaleDateString())
          .fontSize(18)
      }
    }
    .alignItems(HorizontalAlign.Start)
    .width("100%")
    .padding(10)
  }
}