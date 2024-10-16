# 写filter-more的感想

不管怎么说还是写出来了，真的没感觉轻松，还是有挑战性的。

## 最初的挑战和时间线

首先就是阅读量，要先理解BMP图像的储存方式和他给定程序的运行逻辑。这部分内容，阅读原网站去理解他的意思就用了一个晚上（10.14），
然后弄懂程序的运行逻辑又用了一点点下午的时间（10.15），then先实现了前三个，grayscale，reflect和blur，最后一个到今天下午才写出来（10.16）

## 运行逻辑
本质上就是读文件，从中取出像素的RGBTRIPLE信息，构建一个二维数组 来储存RGBTRIPLE，再创建一个struct，让RGBTRIPLE中包含RGB三色的值，以此进行编辑和操作。
**（这里还要注意，他的储存方式是image[列][行]，后面被坑了一次）**

## Grayscale和reverse
难度最低，创建一个int avg即可操作。reflect就创建一个int temp1。但感觉挺啰嗦的，不过也没想到比较好的方式简化

## Blur
一个坑点是：原图片的像素在编辑时不能有所修改，要不然就会影响后续结果。一开始是有考虑到这个问题的，
写着写着就忘了，从昨晚debug到今天下午。。最后还是cs50duck帮忙搞出来的。。有被自己无语到。以后，想到的注意事项可以考虑写进一个注释放在程序开头，
debug的时候就看一下，没准会节省很多时间。

## Edge
blur写完之后其实也很明确了，创建2个二维数组，然后写循环迭代算就可以了（这个循环还可以直接copy Blur里面的😄），但一开始想复杂了，要在循环里搞骚操作，最后没弄出来。。
最后一个坑点就是要注意RGB的值都不能超过255，超过了直接capped with 255，这个信息是放在倒数第二段的:
>And since channel values can only take on integer values from 0 to 255, 
>be sure the resulting value is rounded to the nearest integer **and capped at 255**(不是哥们，当时这一句直接跳了没去读。。)!
没看仔细，又是duck帮忙🙏真得感谢duck🦆，要不然debug de一个晚上都不一定de 出来

这次就这样，主要还是费时很久，但也没办法，就当锻炼阅读能力了😂
这个程序的其他地方还有很多可取之处，休息一下再去去学习总结。

> To be continued...
