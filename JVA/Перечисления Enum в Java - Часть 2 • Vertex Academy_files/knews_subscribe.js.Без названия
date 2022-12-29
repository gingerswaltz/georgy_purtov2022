jQuery(document).ready(function() {
	knewsfunc = function() {
		if (jQuery(this).attr('submitted') !== "true") {
			container = jQuery(this).closest('div.knewsform_container');
			save_knews_form = jQuery(container).html();
			jQuery(this).attr('submitted', "true");
			jQuery("input:text", this).each(function() {
				if (jQuery(this).attr("title") !== undefined) {
					if (jQuery(this).val() == jQuery(this).attr("title")) jQuery(this).val("");
				}
			});
			jQuery.post(jQuery(this).attr('action'), jQuery(this).serialize(), function (data) { 
					jQuery(container).html(data);
					jQuery('a.knews_back', container).click( function () {
						jQuery(container).html(save_knews_form);
						return false;								
					});
				});
		}
		return false;
	};
	if (parseInt(jQuery.fn.jquery.split('.').join(''), 10) >= 170) {
		jQuery(document).on('submit', 'div.knewsform_container form', knewsfunc);
	} else {
		jQuery('div.knewsform_container form').live('submit', knewsfunc);						
	}
})
