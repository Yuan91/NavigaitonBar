
 # iOS 导航栏属性研究

 ## 影响导航栏布局的属性
 `translucent`
 `edgesForExtendedLayout`
 `extendedLayoutIncluedsOpaqueBars`
 `automaticallyAdjustScrollViewInsets` | `contentInsetAdjustmentBehavior`
 
 ## 对于各个属性的解读

 1.`translucent`

 来由:iOS7 导航栏增加了`translucent`(半透明)效果.

 默认值:`YES`,体现为毛玻璃效果,可以看到下边的视图.如果设置为`NO`,导航栏颜色为白色.
 
 影响:导航栏颜色的设置 和 `ViewController` 下控件的布局; 同时,对于导航栏的颜色/背景图的设置,也会影响这个属性
 
 iOS中关于透明度的属性:

 `transparent` 全透明. `UINavigationBar`和`UIView` 均不具备这个属性

 `opaque` 不透明.`BOOL`值.  `UIView`的属性, 不会影响导航栏的透明效果

 `alpha` 透明度. `float`值. `UIView`有这个属性,颜色值也会有这属性,所有说`alpha`值的时候,要区分是说控件的透明度还是颜色值的`alpha`通道

 `opacity` 透明度. `float`值. `CALayer` 的属性. `View.alpha = CALayer.opacity`
 
 
 2.`edgesForExtendedLayout`

 来由: iOS7 `ViewController` 默认使用 full-Screen 布局,也就是说`ViewController`的大小 和屏幕大小一致.
 但是开发者可以通过`ViewController`的`edgesForExtendedLayout`属性来调整,是否让`ViewController`延伸到屏幕边缘.

 使用场景:该特性主要是处理,当前界面有导航栏或者`tabBar`时,`ViewController`的显示区域问题,例如设置`edgesForExtendedLayout`为`UIRectEdgeNone`时,则`ViewController`不会被导航栏和`tabBar` 所遮挡.
 默认值为:`UIRectEdgeAll`

 注意点:只有当`ViewController`被嵌到别的`container view controller`中时才会起作用,例如`UINavigationController`
 
 3.`extendedLayoutIncluedsOpaqueBars`

 来由:iOS 7启用,在导航栏不透明时,调整`ViewController`与屏幕的对齐方式. 当导航栏为不透明时,发现`ViewController` 顶部没有与屏幕顶部对齐,即便设置`edgesForExtendedLayout` 为`UIRectEdgeAll` 或者 `UIRectEdgeTop` 也没有作用,这个时候就需要启用`extendedLayoutIncluedsOpaqueBars`属性
 默认值为`NO`

 使用场景: 当导航栏为不透明时,想要通过`edgesForExtendedLayout` 调整`ViewController` 与屏幕的对齐方式时,需要 使用这个属性(设置为`YES`)

 
 4.`automaticallyAdjustScrollViewInsets` | `contentInsetAdjustmentBehavior`

 来源:`automaticallyAdjustScrollViewInsets` iOS 7启用,iOS 11废弃,默认值是YES
 `contentInsetAdjustmentBehavior` iOS 11启用,默认值`UIScrollViewContentInsetAdjustmentAutomatic`. 该属性用来代替`automaticallyAdjustScrollViewInsets`
 
 使用场景:

①这两个属性,都是为了解决 透明导航栏时 且`scrollView`及其子类 是控制器的第一个子视图的时候,`scrollView` 与 `UINavigationController` 的对齐问题.
值得注意的是,这个时候,`UINavigationController/ViewController/ScrollView` 三者的顶部仍然是对齐的,与屏幕顶部保持一致.只是系统调整了 `scrollView` 的 `contentInset`(在iOS 11及之后,表现为`adjustedContentInset`)
 
 ②当导航栏为透明时,`ViewController` 的第一个子视图不是 `ScrollView` ,系统并不会调整其位置
 
 ③当导航栏被隐藏时,`ViewController` 的第一个视图是`ScrollView`, 也会被自动调整位置
 
 
 ## 属性之间的相互影响
 1.从`translucent` 说起

 设置为`YES`时:

 ①`edgesForExtendedLayout` 默认为 `UIRectEdgeAll`

 ②当`scrollView` 为`ViewController`第一个子视图时,系统会调整`contentInset`使其从导航栏下面显示;如果非`scrollView`视图,则不会调整. 如果此时,我们想调整`scrollView`的偏移量可以通过`automaticallyAdjustScrollViewInsets | contentInsetAdjustmentBehavior` 来设置

 设置为`NO`时:

 `edgesForExtendedLayout` 默认为 `UIRectEdgeLeft | UIRectEdgeRight | UIRectEdgeBottom`,不会顶部对齐.
 如果 此时想要设置 `ViewController` 对齐屏幕顶部,可以通过`extendedLayoutIncluedsOpaqueBars`
 
 当隐藏导航时,不管`translucent` 如何设置,对于第一个子视图是`scrollView的ViewController`系统仍会调整它的偏移量
 
 2.`translucent` 与 `UINavigationBar.backgroundImage` 的相关影响

 `translucent` 默认是`YES`

 ①当未设置`translucent` 时,它的值受`backgroundImage`图片像素点`alpha`值的影响
 使用`[setBackgroundImage:forBarMetrics:] `设置背景图
如果图片中有像素点小于1,系统会推断`translucent` 为`YES`
当所有像素点`alpha`值为1的时候,系统会推断`translucent`为`NO`.

 ②系统也会根据`translucent`的值,也修改`backgroundImage`的透明度

当`translucent为YES`时,设置了一个完全不透明的图片,系统会自动修正这个图片并为它添加一个透明度，用于模拟 `translucent` 效果。

当`translucent`为`NO`时,设置了一个带有透明效果的图片,系统会在这个带有透明效果的图片背后，添加一个不透明的纯色图片用于整体效果的合成.
这个纯色图片的颜色取决于 `barStyle` 属性，当属性为 `UIBarStyleBlack` 时为黑色，当属性为 `UIBarStyleDefault` 时为白色，如果我们设置了 `barTintColor`，则以设置的颜色为基准。
 
 参考链接:

 [iOS 导航栏的那些事儿](https://www.jianshu.com/p/c8ffb2bdda91)

 [美团点评：iOS系统中导航栏的转场解决方案与最佳实践](https://tech.meituan.com/2018/10/25/navigation-transition-solution-and-best-practice-in-meituan.html)

 
 

