@Entry
@Component
struct GridExample {
  build() {
    Grid() {
      GridComItem()
      GridComItem()
      GridComItem()
      GridComItem()
      GridComItem()
      GridComItem()
      GridComItem()
      GridComItem()
      GridComItem()
      GridComItem()
      GridComItem()
      GridComItem()
    }
    .width("100%")
    .height("100%")
    .backgroundColor(Color.Gray)
    .columnsTemplate("1fr 1fr 1fr")
    .columnsGap(10)
    .rowsGap(10)
    .padding(10)
  }
}

@Component
struct GridComItem {
  build() {
    GridItem() {
      Column({space:18}) {
        Image($r("app.media.startIcon"))
          .width(50)
        Text("京东")
          .fontSize(30)
      }
    }
    .width("100%")
    .height(128)
    .backgroundColor(Color.White)
    .padding(10)
  }
}
