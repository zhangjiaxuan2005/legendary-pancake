import { LengthMetrics } from '@kit.ArkUI'

@Entry
@Component
struct FlexExample {
  build() {
    Column({ space: 12 }) {
      Text("阶段选择")
        .fontSize(42)
        .fontWeight(FontWeight.Bold)
        .padding({ left: 10 })
      Flex({
        wrap: FlexWrap.Wrap,
        space: {
          main: LengthMetrics.vp(3) ,
          cross: LengthMetrics.vp(4)
        }
      }) {
        Text("ArkUI")
          .backgroundColor("#c6c6c6")
          .borderRadius(4)
          .padding(4)
          .fontSize(20)
        Text("ArkTS")
          .backgroundColor("#c6c6c6")
          .borderRadius(4)
          .padding(4)
          .fontSize(20)
        Text("界面开发")
          .backgroundColor("#c6c6c6")
          .borderRadius(4)
          .padding(4)
          .fontSize(20)
        Text("系统能力")
          .backgroundColor("#c6c6c6")
          .borderRadius(4)
          .padding(4)
          .fontSize(20)
        Text("权限控制")
          .backgroundColor("#c6c6c6")
          .borderRadius(4)
          .padding(4)
          .fontSize(20)
        Text("元服务")
          .backgroundColor("#c6c6c6")
          .borderRadius(4)
          .padding(4)
          .fontSize(20)
      }
    }
    .alignItems(HorizontalAlign.Start)
    .width("100%")
    .padding(10)
    .height("100%")
  }
}