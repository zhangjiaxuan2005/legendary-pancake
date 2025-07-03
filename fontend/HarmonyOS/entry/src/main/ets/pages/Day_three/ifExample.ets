@Entry
@ComponentV2
struct IfExample {
  @Local IsShow: boolean = true

  build() {
    Column({ space: 10 }) {
      Toggle({
        type: ToggleType.Switch,
        isOn: $$this.IsShow, //$$双向绑定
      })
      // .onChange((value)=>{
      //   this.IsShow=value
      // })
      if (this.IsShow) {
        Text("你好")
      }
    }
    .width("100%")
  }
}