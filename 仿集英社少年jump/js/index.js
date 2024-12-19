// index.js
$('.slideshow').each(function () {
    var $slideshow = $(this);
    $slideshow.imagesLoaded(function () {
        $slideshow.skidder({
            slideClass: '.slide',
            animationType: 'css',
            scaleSlides: true,
            maxWidth: 300,
            maxHeight: 238,
            paging: true,
            autoPaging: true,
            pagingWrapper: ".skidder-pager",
            pagingElement: ".skidder-pager-dot",
            swiping: true,
            leftaligned: false,
            cycle: true,
            jumpback: false,
            speed: 400,
            autoplay: false,
            autoplayResume: false,
            interval: 4000,
            transition: "slide",
            afterSliding: function () { },
            afterInit: function () { }
        });
    });
});
$(window).smartresize(function () {
    $('.slideshow').skidder('resize');
});
document.addEventListener('DOMContentLoaded', function () {
    var ticker = document.getElementById('ticker');
    var span = ticker.querySelector('span');

    // 暂停滚动
    function pauseScroll() {
        span.style.animationPlayState = 'paused';
    }

    // 继续滚动
    function resumeScroll() {
        span.style.animationPlayState = 'running';
    }

    // 鼠标悬停时暂停滚动，鼠标离开时继续滚动
    ticker.addEventListener('mouseover', pauseScroll);
    ticker.addEventListener('mouseout', resumeScroll);
});