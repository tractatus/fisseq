hist.match.ics<-function(file=system.file('06_N1_2_2016_10_10_10_10_10.ics', package='fisseq'), plot=TRUE, verbose=TRUE){
  output<-.Call("readICS", file, as.integer(verbose))

  images<-length(output$histo)/2047
  zstacks<-images/4
  output.data.tmp<-matrix(output$histo, ncol=images )

  output.data<-list()

  intensities<-lapply(seq(1,length(output$range),by=2), function(x){ seq(output$range[x], output$range[x+1], length.out=2047) } )
  intensities<-do.call("cbind", intensities)

  output.data[[1]]<-list(pixels=output.data.tmp[,1:zstacks], intensity= intensities[,1:zstacks])
  output.data[[2]]<-list(pixels=output.data.tmp[,1:zstacks+zstacks*1], intensity= intensities[,1:zstacks] )
  output.data[[3]]<-list(pixels=output.data.tmp[,1:zstacks+zstacks*2], intensity= intensities[,1:zstacks]  )
  output.data[[4]]<-list(pixels=output.data.tmp[,1:zstacks+zstacks*3], intensity= intensities[,1:zstacks] )


  if(plot){

    if(.Platform$OS.type=="windows") {
      quartz<-function() windows()
    }

    quartz( width=4, height=9.2)
    par(mar=c(4,6,4,6), mfrow=c(4,1))

    ecdf.plot<-function(pixels, intensity, ch='Channel 1', color=rgb(0,1,0), transparency=20 ){
      maximum<-max(cumsum(pixels[,1]))
      xMax<-ceiling(round( max(intensity[which(round(cumsum(rowMeans(pixels))/maximum,2) == 0.99, arr.ind=TRUE)[1], ])/1000, 1))*1000-950
      plot(intensity[,1], cumsum(pixels[,1]), type='l', xlim=c(0, xMax), col=paste(color, transparency, sep=''),  ylab='Quantile', xlab='Pixel intensity', axes=FALSE, main=ch)
      axis(1)
      axis(2, at=c(0,maximum*0.5,maximum), labels=c(0,0.5,1), las=1)
      axis(4, at=c(0,maximum*0.5,maximum), labels=c(0,round(maximum*0.5/10^6, 2), round(maximum/10^6, 2)), las=1)
      mtext('Mega pixels', 4, 3, cex=0.7 )

      lapply(1:zstacks, function(x){lines(intensity[,x], cumsum(pixels[,x]), col=paste(color, transparency, sep='') ) })

      fit<-smooth.spline(intensity[,1], cumsum(pixels[,1]))
      smoothed<-predict(fit, seq(0,xMax))$y
      for(i in 1:zstacks){
        fit<-smooth.spline(intensity[,i], cumsum(pixels[,i]))
        smoothed<-rbind(smoothed, predict(fit, seq(0,xMax))$y )
      }

      quant<-apply(smoothed, 2, function(x){quantile(x,0.5)})



      lines(quant, col='black', lwd=3 )
      lines(quant, col=color, lwd=1.5 )

      ED50<-which.min(abs(quant-maximum/2))

      lines(c(-1000 , ED50), rep(quant[ED50],2))
      lines(rep(ED50,2), c(-1000, quant[ED50]))
      points(ED50, quant[ED50], pch=21, bg='orange')
      abline(h=c(-1000, maximum), lty=2, col='darkgray')

      ED95<-which.min(abs(quant-maximum*0.95))
      ED05<-which.min(abs(quant-maximum*0.05))

      legend('bottomright', c(paste('Median = ',ED50), paste('95% quantile = ',ED95), paste('5% quantile = ',ED05)), pch=c(21,NA,NA), pt.bg='orange', box.lty = 0)
    }

    ecdf.plot(output.data[[1]]$pixels, output.data[[1]]$intensity, ch='Channel 1', color=rgb(0,1,1), transparency=30)
    ecdf.plot(output.data[[2]]$pixels, output.data[[2]]$intensity, ch='Channel 2', color=rgb(1,0,1), transparency=30)
    ecdf.plot(output.data[[3]]$pixels, output.data[[3]]$intensity, ch='Channel 3', color=rgb(0,1,0), transparency=30)
    ecdf.plot(output.data[[4]]$pixels, output.data[[4]]$intensity, ch='Channel 4', color=rgb(1,0,0), transparency=30)


  }
  return(output)
}
