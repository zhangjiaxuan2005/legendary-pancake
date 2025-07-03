@Entry
@Component
struct RCExample {
  build() {
    Column() {
      RelativeContainer() {
        Row().width(100).height(100).backgroundColor(Color.White).id('WhiteBox')
          .alignRules({
          center:{
            anchor:'__container__',
            align:VerticalAlign.Center
          }
        })
        Row().width(100).height(100).backgroundColor(Color.Blue).id('BlueBox')
          .alignRules({
            middle:{
              anchor:'__container__',
              align:HorizontalAlign.Center
            }
          })

        Row().width(100).height(100).backgroundColor(Color.Brown)
          .alignRules({
            middle:{
              anchor:'__container__',
              align:HorizontalAlign.Center
            },
            top:{
              anchor:'WhiteBox',
              align:VerticalAlign.Bottom
            }
          })
        Row().width(100).height(100).backgroundColor(Color.Orange)
          .alignRules({
            center:{
              anchor:'__container__',
              align:VerticalAlign.Center
            },
            left:{
              anchor:'BlueBox',
              align:HorizontalAlign.End
            }
          })
      }
      .backgroundColor(Color.Grey)
      .width(300)
      .height(300)
    }
    .backgroundColor(Color.Pink)
    .width("100%")
    .height("100%")
  }
}