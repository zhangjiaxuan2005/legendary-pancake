@Entry
@Component
struct RowAndColumn {
  build() {
    Column({ space: 2 }) {
      Row({ space: 1 }) {
        Row().width(20).height(20).border({ width: 2 })
        Row().width(20).height(20).border({ width: 2 })
        Row().width(20).height(20).border({ width: 2 })
        Row().width(20).height(20).border({ width: 2 })
        Row().width(20).height(20).border({ width: 2 })
        Row().width(20).height(20).border({ width: 2 })
      }
      //布局主方向
      .justifyContent(FlexAlign.Center)
      //侧轴方向
      .alignItems(VerticalAlign.Center)
      .width(200)
      .height(100)
      .border({
        width: 2,
        color: 'red',
        radius: 10,
        style: BorderStyle.Dashed
      })

      Column({ space: 1 }) {
        Row().width(20).height(20).border({ width: 2 })
        Row().width(20).height(20).border({ width: 2 })
        Row().width(20).height(20).border({ width: 2 })
        Row().width(20).height(20).border({ width: 2 })
        Row().width(20).height(20).border({ width: 2 })
        Row().width(20).height(20).border({ width: 2 })
      }
      .justifyContent(FlexAlign.Center)
      .width(200)
      .height(300)
      .border({
        width: 2,
        color: 'red',
        radius: 10,
        style: BorderStyle.Dashed
      })

      Row() {
        Row().width(30).height(30).border({ width: 2 })
        Row().width(30).height(30).border({ width: 2 })
        Row().width(30).height(30).border({ width: 2 })
        Row().width(30).height(30).border({ width: 2 })
        Row().width(30).height(30).border({ width: 2 })
        Row().width(30).height(30).border({ width: 2 })
      }
      .justifyContent(FlexAlign.SpaceBetween) //两端对齐
      .width(200)
      .height(100)
      .border({
        width: 2,
        color: 'red',
        radius: 10,
        style: BorderStyle.Dashed
      })

      Row() {
        Row().width(30).height(30).border({ width: 2 })
        Row().width(30).height(30).border({ width: 2 })
        Row().width(30).height(30).border({ width: 2 })
        Row().width(30).height(30).border({ width: 2 })
      }
      .justifyContent(FlexAlign.SpaceAround) //间隙环绕
      .width(200)
      .height(100)
      .border({
        width: 2,
        color: 'red',
        radius: 10,
        style: BorderStyle.Dashed
      })

      Row() {
        Row().width(30).height(30).border({ width: 2 })
        Row().width(30).height(30).border({ width: 2 })
        Row().width(30).height(30).border({ width: 2 })
        Row().width(30).height(30).border({ width: 2 })
      }
      .justifyContent(FlexAlign.SpaceEvenly) //间隙等分
      .width(200)
      .height(100)
      .border({
        width: 2,
        color: 'red',
        radius: 10,
        style: BorderStyle.Dashed
      })
    }
    .width("100%")
    .height("100%")
  }
}