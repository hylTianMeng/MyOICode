r){
            int mid=(l+r+1)>>1;
            if(Check(mid)) l=mid;
            else r=mid-1;
        }